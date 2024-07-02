#include "MCTSNode.h"

UMCTSNode::UMCTSNode()
    : Parent(nullptr), Action(nullptr), VisitCount(0), TotalReward(0.0f)
{
}

void UMCTSNode::InitializeNode(UMCTSNode* InParent, UAction* InAction)
{
    Parent = InParent;
    Action = InAction;
    VisitCount = 0;
    TotalReward = 0.0f;
    Children.Empty();
}

FString UMCTSNode::GetState() const
{
    // �� �Լ��� ���� ������ ������Ʈ�� ���� ǥ�� ��Ŀ� ���� �޶��� �� �ֽ��ϴ�.
    // ���� ���, ���� ������ ����, ĳ������ ��ġ, ���ҽ� ���� ���� ���ڿ��� ��ȯ�� �� �ֽ��ϴ�.
    // ���⼭�� ������ ���ø� �����մϴ�.

    if (Action)
    {
        return FString::Printf(TEXT("Node with Action: %s"), *Action->GetName());
    }
    else
    {
        return TEXT("Root Node");
    }
}
