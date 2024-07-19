#include "MCTS.h"
#include "Kismet/KismetMathLibrary.h"

UMCTS::UMCTS()
    : RootNode(nullptr), CurrentNode(nullptr), TreeDepth(0), ExplorationParameter(1.41f), World(nullptr)
{
}


void UMCTS::InitializeMCTS()
{
    RootNode = NewObject<UMCTSNode>(this);
    RootNode->InitializeNode(nullptr, nullptr);

    FPlatformProcess::Sleep(0.2f);

    if (RootNode != nullptr)
    {
        RootNode->VisitCount = 1;

        UE_LOG(LogTemp, Warning, TEXT("Initialized MCTS"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to Initialize MCTS"));
    }
}


void UMCTS::InitializeCurrentNodeLocate()
{
    UE_LOG(LogTemp, Warning, TEXT("Initialize Current Node Locate"));
    CurrentNode = RootNode;
    TreeDepth = 1;
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
    if(Node == nullptr)
    {
        UE_LOG(LogTemp, Warning,
        TEXT("Node is nullptr, cannot calculate node score"));
        return -FLT_MAX;
    }

    if (Node->VisitCount == 0)
        return FLT_MAX;  // 방문하지 않은 노드 우선 탐색

    if(Node->Parent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Parent node is nullptr, cannot calculate node score"));
		return -FLT_MAX;
	}


    float Exploitation = Node->TotalReward / Node->VisitCount;
    float Exploration = ExplorationParameter * FMath::Sqrt(FMath::Loge((double)Node->Parent->VisitCount) / Node->VisitCount);
    float ObservationSimilarity = CalculateObservationSimilarity(Node->Observation, CurrentObservation);
    float Recency = 1.0f / (1.0f + Node->LastVisitTime);  // 최근 방문일수록 높은 값

    // 동적 탐색 파라미터 계산
    float DynamicExplorationParameter = CalculateDynamicExplorationParameter();


    return Exploitation + DynamicExplorationParameter * Exploration * ObservationSimilarity ;
}


float UMCTS::CalculateDynamicExplorationParameter() const
{
    // 트리의 깊이에 따라 탐색 파라미터 조정
    float DepthFactor = FMath::Max(0.5f, 1.0f - (TreeDepth / 20.0f));

    // 현재까지의 평균 보상에 따라 조정
    float AverageReward = (RootNode->TotalReward / RootNode->VisitCount);
    float RewardFactor = FMath::Max(0.5f, 1.0f - (AverageReward / 100.0f));  // 100은 최대 예상 보상값

    // 시간에 따른 조정 (시간이 지날수록 탐색 감소)
    //float TimeFactor = FMath::Max(0.5f, 1.0f - (World->GetWorld()->GetTimeSeconds() / 300.0f));  // 300초 후 최소값

    return ExplorationParameter * DepthFactor * RewardFactor;
}


float UMCTS::CalculateObservationSimilarity(const FObservationElement& Obs1, const FObservationElement& Obs2) const
{
    // 각 요소의 차이를 계산하고 정규화
    float DistanceDiff = FMath::Abs(Obs1.DistanceToDestination - Obs2.DistanceToDestination) / 100.0f; // 거리를 100으로 나누어 정규화
    float HealthDiff = FMath::Abs(Obs1.AgentHealth - Obs2.AgentHealth) / 100.0f; // 체력을 100으로 나누어 정규화
    float EnemiesDiff = FMath::Abs(Obs1.EnemiesNum - Obs2.EnemiesNum) / 10.0f; // 적의 수를 10으로 나누어 정규화

    // 각 요소에 가중치 적용
    const float DistanceWeight = 0.4f;
    const float HealthWeight = 0.4f;
    const float EnemiesWeight = 0.2f;

    // 가중 맨해튼 거리 계산
    float WeightedDistance = DistanceWeight * DistanceDiff + HealthWeight * HealthDiff + EnemiesWeight * EnemiesDiff;

    // 거리를 유사도로 변환 (지수 감소 함수 사용)
    return FMath::Exp(-WeightedDistance * 5.0f);  // 5.0f는 감소 속도를 조절하는 파라미터
}


void UMCTS::Expand(TArray<UAction*> PossibleActions)
{
    for (UAction* PossibleAction : PossibleActions)
    {
        UMCTSNode* NewNode = NewObject<UMCTSNode>(this);
        if (NewNode != nullptr)
        {
            NewNode->InitializeNode(CurrentNode, PossibleAction);
            NewNode->Observation = CurrentObservation; // 액션에 따른 가상의 관측값 생성
            CurrentNode->Children.Add(NewNode);
            UE_LOG(LogTemp, Warning, TEXT("Expand: Create New Node"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to create a new node"));
        }
    }
}


void UMCTS::Backpropagate()
{
    // 현재 관측값 업데이트
    float DiscountFactor = 0.95f;
    int Depth = 0;

    while (CurrentNode != RootNode)
    {
        CurrentNode->VisitCount++;

        // 효용수치 계산: 즉시 보상과 할인된 미래 보상의 가중 평균
        float ImmediateReward = CalculateImmediateReward(CurrentNode);
        float DiscountedFutureReward = ImmediateReward * FMath::Pow(DiscountFactor, Depth);
        float WeightedReward = (ImmediateReward + DiscountedFutureReward) / 2.0f;

        CurrentNode->TotalReward += WeightedReward;
        UE_LOG(LogTemp, Warning, TEXT("Backpropagate: Update Node - VisitCount: %d, TotalReward: %f"),
			CurrentNode->VisitCount, CurrentNode->TotalReward);

        CurrentNode = CurrentNode->Parent;
        Depth++;
    }

    TreeDepth = 1;
}


float UMCTS::CalculateImmediateReward(UMCTSNode* Node) const
{
    // 현재 노드의 관측값을 기반으로 즉시 보상 계산
    float DistanceReward = 100.0f - Node->Observation.DistanceToDestination;
    float HealthReward = Node->Observation.AgentHealth;
    float EnemyPenalty = -10.0f * Node->Observation.EnemiesNum;

    return DistanceReward + HealthReward + EnemyPenalty;
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


    // 트리 깊이가 10을 넘어가면 중단
    if (TreeDepth >= 10)
	{
        UE_LOG(LogTemp, Warning, TEXT("ShouldTerminate: TreeDepth is over 10"));

		return true;
	}

    // 더 많은 조건을 추가할 수 있음
    return false;
}


void UMCTS::RunMCTS(TArray<UAction*> PossibleActions, UStateMachine* StateMachine)
{
    UE_LOG(LogTemp, Warning, TEXT("RunMCTS Start - CurrentNode: %p, TreeDepth: %d"), CurrentNode, TreeDepth);

    // 트리 깊이 제한에 도달했는지 확인
    if (ShouldTerminate())
    {
        // 역전파 수행
        Backpropagate();

        UE_LOG(LogTemp, Warning, TEXT("Tree depth limit reached. Returning to root node."));
    }

    // 확장 단계
    if (CurrentNode != nullptr && CurrentNode->Children.IsEmpty() && !ShouldTerminate())
    {
        Expand(PossibleActions);
    }

    FPlatformProcess::Sleep(0.2f);

    UMCTSNode* BestChild = SelectChildNode();
    TreeDepth++;

    FPlatformProcess::Sleep(0.2f);

    UE_LOG(LogTemp, Warning, TEXT("Before ExecuteAction - BestChild: %p, Action: %p"), BestChild, BestChild ? BestChild->Action : nullptr);

    if (CurrentNode && BestChild && BestChild->Action)
    {
        CurrentNode = BestChild;

        FPlatformProcess::Sleep(0.2f);

        BestChild->Action->ExecuteAction(StateMachine);
        UE_LOG(LogTemp, Warning, TEXT("After ExecuteAction - CurrentNode: %p, TreeDepth: %d"), CurrentNode, TreeDepth);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to execute action - CurrentNode: %p, BestChild: %p, Action: %p"),
            CurrentNode, BestChild, BestChild ? BestChild->Action : nullptr);
    }
}


FObservationElement UMCTS::GetCurrentObservation(UStateMachine* StateMachine)
{
    // 현재 게임 상태에 따른 관측값 생성
    FObservationElement Observation{};

    Observation.DistanceToDestination = StateMachine->DistanceToDestination;
    Observation.AgentHealth = StateMachine->AgentHealth;
    Observation.EnemiesNum = StateMachine->EnemiesNum;

    return Observation;
}
