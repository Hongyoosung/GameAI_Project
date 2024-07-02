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
    // 이 함수의 실제 구현은 프로젝트의 상태 표현 방식에 따라 달라질 수 있습니다.
    // 예를 들어, 게임 보드의 상태, 캐릭터의 위치, 리소스 상태 등을 문자열로 반환할 수 있습니다.
    // 여기서는 간단한 예시만 제공합니다.

    if (Action)
    {
        return FString::Printf(TEXT("Node with Action: %s"), *Action->GetName());
    }
    else
    {
        return TEXT("Root Node");
    }
}
