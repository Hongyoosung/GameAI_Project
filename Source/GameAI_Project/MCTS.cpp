#include "MCTS.h"
#include "Kismet/KismetMathLibrary.h"

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
    float BestScore = -FLT_MAX;


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

        float Score = CalculateNodeScore(Child);

        if (Score > BestScore)
        {
            BestScore = Score;
            BestChild = Child;
        }
    }

    if (BestChild)
    {
        UE_LOG(LogTemp, Warning, TEXT("Selected Child with UCT Value: %f"), BestScore);

        return BestChild;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No valid child found"));
        return nullptr;
    }
}



float UMCTS::CalculateNodeScore(UMCTSNode* Node) const
{
    if (Node->VisitCount == 0)
        return FLT_MAX;  // �湮���� ���� ��� �켱 Ž��


    float Exploitation = Node->TotalReward / Node->VisitCount;
    float Exploration = ExplorationParameter * FMath::Sqrt(FMath::Loge((double)Node->Parent->VisitCount) / Node->VisitCount);
    float ObservationSimilarity = CalculateObservationSimilarity(Node->Observation, CurrentObservation);
    float Recency = 1.0f / (1.0f + Node->LastVisitTime);  // �ֱ� �湮�ϼ��� ���� ��

    const float C = 1.0f;  // Ž��-Ȱ�� ���� ���
    const float D = 0.5f;  // ������ ���絵 ����ġ
    const float E = 0.3f;  // �ֱټ� ����ġ

    return Exploitation + C * Exploration + D * ObservationSimilarity + E * Recency;
}


float UMCTS::CalculateObservationSimilarity(const FObservationElement& Obs1, const FObservationElement& Obs2) const
{
    // �� ����� ���̸� ����ϰ� ����ȭ
    float DistanceDiff = FMath::Abs(Obs1.DistanceToDestination - Obs2.DistanceToDestination) / 100.0f; // �Ÿ��� 100���� ������ ����ȭ
    float HealthDiff = FMath::Abs(Obs1.AgentHealth - Obs2.AgentHealth) / 100.0f; // ü���� 100���� ������ ����ȭ
    float EnemiesDiff = FMath::Abs(Obs1.EnemiesNum - Obs2.EnemiesNum) / 10.0f; // ���� ���� 10���� ������ ����ȭ

    // �� ��ҿ� ����ġ ����
    const float DistanceWeight = 0.4f;
    const float HealthWeight = 0.4f;
    const float EnemiesWeight = 0.2f;

    // ���� ����ư �Ÿ� ���
    float WeightedDistance = DistanceWeight * DistanceDiff + HealthWeight * HealthDiff + EnemiesWeight * EnemiesDiff;

    // �Ÿ��� ���絵�� ��ȯ (���� ���� �Լ� ���)
    return FMath::Exp(-WeightedDistance * 5.0f);  // 5.0f�� ���� �ӵ��� �����ϴ� �Ķ����
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
            NewNode->Observation = CurrentObservation; // �׼ǿ� ���� ������ ������ ����
            CurrentNode->Children.Add(NewNode);
            UE_LOG(LogTemp, Warning, TEXT("Create New Node"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to create a new node"));
        }
    }


    TreeDepth++;
}


void UMCTS::Backpropagate(float InReward)
{
    float DiscountFactor = 0.95f;

    while (CurrentNode != RootNode)
    {
        CurrentNode->VisitCount++;
        CurrentNode->TotalReward += InReward;


        UE_LOG(LogTemp, Warning, TEXT("Node Updated - VisitCount: %d, TotalReward: %f"),
            CurrentNode->VisitCount, CurrentNode->TotalReward);

        InReward *= DiscountFactor;  // ���ε� ����
        CurrentNode = CurrentNode->Parent;
    }
}


// ���� ���� ���� �Լ�
bool UMCTS::ShouldTerminate() const
{
    // currentnode�� null�̸� �ߴ�
    if (CurrentNode == nullptr)
	{
        UE_LOG(LogTemp, Warning, TEXT("ShouldTerminate: CurrentNode is nullptr"));
		return true;
	}

    // �湮 Ƚ���� 1000�� ������ �ߴ�
    if (CurrentNode->VisitCount > 1000)
    {
        UE_LOG(LogTemp, Warning, TEXT("ShouldTerminate: CurrentNode VisitCount is over 1000"));

        return true;
    }

    // ������ Ư�� ���� ������ �ߴ�
    if (CurrentNode->TotalReward > 1000.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("ShouldTerminate: CurrentNode Reward is over 1000"));
        return true;
    }

    // Ʈ�� ���̰� 10�� �Ѿ�� �ߴ�
    if (TreeDepth > 20)
	{
        UE_LOG(LogTemp, Warning, TEXT("ShouldTerminate: TreeDepth is over 10"));

		return true;
	}

    // �� ���� ������ �߰��� �� ����
    return false;
}


void UMCTS::RunMCTS(TArray<UAction*> PossibleActions, float Reward, UStateMachine* StateMachine)
{
    // ���� ������ ������Ʈ
    CurrentObservation = GetCurrentObservation(StateMachine);

    // Ȯ�� �ܰ�
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


FObservationElement UMCTS::GetCurrentObservation(UStateMachine* StateMachine)
{
    // ���� ���� ���¿� ���� ������ ����
    FObservationElement Observation{};

    Observation.DistanceToDestination = StateMachine->DistanceToDestination;
    Observation.AgentHealth = StateMachine->AgentHealth;
    Observation.EnemiesNum = StateMachine->EnemiesNum;

    return Observation;
}
