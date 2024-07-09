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
        return FLT_MAX;  // 방문하지 않은 노드 우선 탐색

    float Exploitation = Node->TotalReward / Node->VisitCount;
    float Exploration = ExplorationParameter * FMath::Sqrt(FMath::Loge((double)Node->Parent->VisitCount) / Node->VisitCount);
    float ObservationSimilarity = CalculateObservationSimilarity(Node->Observation, CurrentObservation);
    float Recency = 1.0f / (1.0f + Node->LastVisitTime);  // 최근 방문일수록 높은 값

    const float C = 1.0f;  // 탐색-활용 균형 상수
    const float D = 0.5f;  // 관측값 유사도 가중치
    const float E = 0.3f;  // 최근성 가중치

    return Exploitation + C * Exploration + D * ObservationSimilarity + E * Recency;
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
    if (ShouldTerminate())
    {
        UE_LOG(LogTemp, Warning, TEXT("ShouldTerminate is true, cannot expand"));
        return;
    }

    TArray<UMCTSNode*> NewNodes;

    for (UAction* PossibleAction : PossibleActions)
    {
        UMCTSNode* NewNode = NewObject<UMCTSNode>(this);
        if (NewNode != nullptr)
        {
            NewNode->InitializeNode(CurrentNode, PossibleAction);
            NewNode->Observation = CurrentObservation; // 액션에 따른 가상의 관측값 생성
            NewNodes.Add(NewNode);
            UE_LOG(LogTemp, Warning, TEXT("Create New Node"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to create a new node"));
        }
    }

    // 관측값 클러스터링 적용
    TArray<UMCTSNode*> ClusteredNodes = HashClusterNodes(NewNodes, 5);  // 최대 5개의 클러스터

    CurrentNode->Children = ClusteredNodes;

    TreeDepth++;
}




FObservationElement UMCTS::GenerateObservation(UAction* Action)
{
    // 액션에 따른 가상의 관측값 생성 로직
    // 이 부분은 게임의 특성에 맞게 구현해야 합니다.
    return FObservationElement();
}


void UMCTS::Backpropagate(UMCTSNode* Node, float InReward)
{
    float DiscountFactor = 0.95f;

    while (Node != nullptr)
    {
        Node->VisitCount++;
        Node->TotalReward += InReward;


        UE_LOG(LogTemp, Warning, TEXT("Node Updated - VisitCount: %d, TotalReward: %f"),
            Node->VisitCount, Node->TotalReward);

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
    // 현재 관측값 업데이트
    CurrentObservation = GetCurrentObservation(StateMachine);

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
        float SimulationReward = Simulate();
        Backpropagate(BestChild, SimulationReward);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to select a child node"));
        return;
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


float UMCTS::Simulate()
{
    // 실제 게임 로직이나 환경과 연동하여 시뮬레이션을 수행하고 보상을 반환
    // 여기서는 간단한 예시로 대체합니다.
    return FMath::RandRange(-100.0f, 100.0f);
}

TArray<UMCTSNode*> UMCTS::HashClusterNodes(const TArray<UMCTSNode*>& Nodes, int32 HashBuckets)
{
    TMap<int32, UMCTSNode*> Clusters;

    for (UMCTSNode* Node : Nodes)
    {
        int32 HashKey = GetObservationHash(Node->Observation) % HashBuckets;

        if (!Clusters.Contains(HashKey) ||
            Node->VisitCount > Clusters[HashKey]->VisitCount)
        {
            Clusters[HashKey] = Node;
        }
    }

    // 수정된 부분: 값들의 배열을 수동으로 생성
    TArray<UMCTSNode*> ClusteredNodes;
    Clusters.GenerateValueArray(ClusteredNodes);

    return ClusteredNodes;
}

int32 UMCTS::GetObservationHash(const FObservationElement& Obs)
{
    return FCrc::MemCrc32(&Obs, sizeof(FObservationElement));
}