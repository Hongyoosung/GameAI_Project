#include "MCTS.h"

UMCTS::UMCTS()
    : RootNode(nullptr), CurrentNode(nullptr), TreeDepth(0), ExplorationParameter(1.41f)
{
}

void UMCTS::InitializeMCTS()
{
    RootNode = NewObject<UMCTSNode>(this);
    RootNode->InitializeNode(nullptr, nullptr);

    if (RootNode != nullptr)
    {
        CurrentNode = RootNode;
        CurrentNode->VisitCount = 1;

        UE_LOG(LogTemp, Warning, TEXT("Initialized MCTS"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to Initialize MCTS"));
    }
}

UMCTSNode* UMCTS::SelectChildNode(float Reward)
{
    if(ShouldTerminate())
	{
		UE_LOG(LogTemp, Warning, TEXT("ShouldTerminate is true, cannot select child node"));
		return nullptr;
	}


    UMCTSNode* BestChild = nullptr;
    float BestValue = -FLT_MAX;


    if (CurrentNode->Children.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("CurrentNode has no children"));
        return nullptr;
    }


    for (UMCTSNode* Child : CurrentNode->Children)
    {

        if (Child == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("Child node is nullptr"));
            continue;
        }

        float UCT = Child->UCTValue(ExplorationParameter);

        if (UCT > BestValue)
        {
            BestValue = UCT;
            BestChild = Child;
        }
    }

    if (BestChild)
    {
        BestChild->VisitCount++;
        BestChild->Reward += Reward;
        UE_LOG(LogTemp, Warning, TEXT("Selected Child with UCT Value: %f"), BestValue);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No valid child found"));
    }

    CurrentNode = BestChild;

    return CurrentNode;
}

void UMCTS::Expand(TArray<UAction*> PossibleActions)
{
    if (ShouldTerminate())
	{
		UE_LOG(LogTemp, Warning, TEXT("ShouldTerminate is true, cannot expand"));
		return;
	}


    for (UAction* PossibleAction : PossibleActions)
    {
        UMCTSNode* NewNode = NewObject<UMCTSNode>(this);
        if (NewNode != nullptr)
        {
            NewNode->InitializeNode(CurrentNode, PossibleAction);
            CurrentNode->Children.Add(NewNode);

            UE_LOG(LogTemp, Warning, TEXT("Expanded Node"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to create a new node"));
        }
    }

    TreeDepth++;
}

float UMCTS::Simulate()
{
    return FMath::RandRange(-100.0f, 100.0f);
}

float UMCTS::Backpropagate(UMCTSNode* Node, float InReward)
{
    // 총합 보상
    float TotalReward = 0.0f;

    while (Node)
    {
        Node->VisitCount++;
        Node->Reward += InReward;
        UE_LOG(LogTemp, Warning, TEXT("VisitCount: %d, Reward: %f"), Node->VisitCount, Node->Reward);
        Node = Node->Parent;

        TotalReward += InReward;
    }

    CurrentNode = RootNode;

    return TotalReward;
}

// 조기 종료 조건 함수
bool UMCTS::ShouldTerminate() const
{
    // currentnode가 null이면 중단
    if (CurrentNode == nullptr)
	{
        UE_LOG(LogTemp, Warning, TEXT("ShouldTerminate: CurrentNode is nullptr"));
		return true;
	}

    // 방문 횟수가 1000을 넘으면 중단
    if (CurrentNode->VisitCount > 1000)
    {
        UE_LOG(LogTemp, Warning, TEXT("ShouldTerminate: CurrentNode VisitCount is over 1000"));

        return true;
    }

    // 보상이 특정 값을 넘으면 중단
    if (CurrentNode->Reward > 1000.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("ShouldTerminate: CurrentNode Reward is over 1000"));
        return true;
    }

    // 트리 깊이가 10을 넘어가면 중단
    if (TreeDepth > 10)
	{
        UE_LOG(LogTemp, Warning, TEXT("ShouldTerminate: TreeDepth is over 10"));

		return true;
	}

    // 더 많은 조건을 추가할 수 있음
    return false;
}

void UMCTS::RunMCTS(TArray<UAction*> PossibleActions, float Reward, UStateMachine* StateMachine)
{
    if (CurrentNode->Children.IsEmpty())
    {
        Expand(PossibleActions);
    }

    FPlatformProcess::Sleep(0.2f);

    UMCTSNode* BestChild = SelectChildNode(Reward);

    FPlatformProcess::Sleep(0.2f);

    if (BestChild && BestChild->Action)
    {
        BestChild->Action->ExecuteAction(StateMachine);
    }
    else
    {
        CurrentNode = RootNode;
    }
}