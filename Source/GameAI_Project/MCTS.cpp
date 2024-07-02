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

void UMCTS::InitializeRootNode()
{
    CurrentNode = RootNode;
}

UMCTSNode* UMCTS::SelectChildNode()
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

        float UCT = CalculateUCT(Child);

        if (UCT > BestValue)
        {
            BestValue = UCT;
            BestChild = Child;
        }
    }

    if (BestChild)
    {
        UE_LOG(LogTemp, Warning, TEXT("Selected Child with UCT Value: %f"), BestValue);

        return BestChild;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No valid child found"));
        return nullptr;
    }
}

float UMCTS::CalculateUCT(UMCTSNode* Node) const
{
    if (Node->VisitCount == 0)
        return FLT_MAX;  // 방문하지 않은 노드 우선 탐색

    float Exploitation = Node->TotalReward / Node->VisitCount;
    float Exploration = ExplorationParameter * FMath::Sqrt(FMath::Loge((double)Node->Parent->VisitCount) / Node->VisitCount);

    return Exploitation + Exploration;
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

void UMCTS::Backpropagate(UMCTSNode* Node, float InReward)
{
    float DiscountFactor = 0.95f;

    while (Node != nullptr)
    {
        Node->VisitCount++;
        Node->TotalReward += InReward;

        UE_LOG(LogTemp, Warning, TEXT("Node Updated - VisitCount: %d, TotalReward: %f, AverageReward: %f"),
            Node->VisitCount, Node->TotalReward, Node->TotalReward / Node->VisitCount);

        InReward *= DiscountFactor;  // 할인된 보상
        Node = Node->Parent;
    }
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
    if (CurrentNode->TotalReward > 1000.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("ShouldTerminate: CurrentNode Reward is over 1000"));
        return true;
    }

    // 트리 깊이가 10을 넘어가면 중단
    if (TreeDepth > 20)
	{
        UE_LOG(LogTemp, Warning, TEXT("ShouldTerminate: TreeDepth is over 10"));

		return true;
	}

    // 더 많은 조건을 추가할 수 있음
    return false;
}

void UMCTS::RunMCTS(TArray<UAction*> PossibleActions, float Reward, UStateMachine* StateMachine)
{
    // 확장 단계
    if (CurrentNode != nullptr && CurrentNode->Children.IsEmpty() && !ShouldTerminate())
    {
        Expand(PossibleActions);
    }

    FPlatformProcess::Sleep(0.2f);

    UMCTSNode* BestChild = SelectChildNode();

    FPlatformProcess::Sleep(0.2f);

    if (BestChild && BestChild->Action)
    {
        BestChild->Action->ExecuteAction(StateMachine);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to select a child node"));

        return;
    }
}