#include "MCTSNode.h"

UMCTSNode::UMCTSNode()
    : Parent(nullptr), Action(nullptr), Reward(0.0f), VisitCount(0)
{
}

void UMCTSNode::InitializeNode(UMCTSNode* InParent, UAction* InAction)
{
    Parent = InParent;
    Action = InAction;
    Reward = 0.0f;
    VisitCount = 0;
}

float UMCTSNode::UCTValue(float ExplorationParameter) const
{
    // print visitcount
    UE_LOG(LogTemp, Warning, TEXT("VisitCount: %d"), VisitCount);

    if (VisitCount == 0)
    {
        return FLT_MAX; // �湮 Ƚ���� 0�� ���, UCT ���� ���Ѵ�� �����Ͽ� Ž���ϵ��� ��
    }

    // Check if Parent is null
    if (Parent == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Parent is null"));

        return 0.0f; // ���� �� ������ ������ ����
    }
    if (Parent->VisitCount == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Parent VisitCount is 0"));

        return 0.0f; // ���� �� ������ ������ ����
    }

    float Exploitation = Reward / VisitCount;
    float Exploration = ExplorationParameter * FMath::Sqrt(FMath::Loge((double)Parent->VisitCount) / VisitCount);

    // print exploitation and exploration
    UE_LOG(LogTemp, Warning, TEXT("Exploitation: %f, Exploration: %f"), Exploitation, Exploration);

    //return Exploitation + Exploration;

    return Exploitation + Exploration;
}
