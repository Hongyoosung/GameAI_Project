# SDAEP(State-Based Dynamic Action Expansion Planning Model)
![Unreal Engine](https://img.shields.io/badge/unrealengine-%23313131.svg?style=for-the-badge&logo=unrealengine&logoColor=white) ![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

> This system, inspired by Monte Carlo Tree Search (MCTS), allows an agent to dynamically expand and plan its actions based on the current state through tree expansion and selection algorithms applied to a state-based system with a reinforcement learning model.

+ **FSM**: Each state has a set of possible actions. A tree search object exists for each state, which expands and plans actions within the state. The FSM ensures that the agent's actions are organized and executed according to the current state, maintaining a structured approach to state transitions and action selections.

+ **Tree Expansion and Search Algorithm**: Based on the current state, possible actions are expanded into a tree structure, selecting and executing the optimal child node. The reward values help find the optimal action plan. This algorithm evaluates different action paths and selects the most promising one, continuously refining the agent's strategy through exploration and exploitation.

+ **Reinforcement Learning Model**: Manages state transitions. It handles the game environment and observational data, updating reward values based on actions performed by the tree search algorithm. The reinforcement learning model adapts to the environment by learning from the rewards received, optimizing the agent's behavior over time.

+ **Interaction of Components**: The FSM defines the structure of states and possible actions. Within each state, the tree search algorithm explores and selects optimal actions, guided by the reinforcement learning model's rewards. The reinforcement learning model updates its policy based on the outcomes of these actions, informing future decisions. This integrated approach ensures that the agent can make informed and optimized decisions dynamically, adapting to changes in the environment and improving its performance over time.

#

</br>

> 이 시스템은 몬테카를로 트리 탐색(MCTS)에 영감을 받아 상태 기반과 강화학습 모델이 적용된 시스템입니다. 트리 확장 및 선택 알고리즘을 통해 에이전트가 현재 상태에 기반하여 동적으로 행동을 확장하고 계획할 수 있게 합니다.

+ **FSM (유한 상태 기계)**: 각 상태마다 가능한 행동 집합이 존재합니다. 각 상태에는 트리 탐색 객체가 있으며, 이 객체를 통해 상태 내에서 행동을 확장하고 계획합니다. FSM은 에이전트의 행동이 현재 상태에 따라 조직되고 실행되도록 보장하며, 상태 전환과 행동 선택의 구조적인 접근을 유지합니다.

+ **트리 확장 및 탐색 알고리즘**: 현재 상태를 기반으로 가능한 행동들을 트리 형태로 확장하고, 최적의 자식 노드를 선택하고 실행합니다. 보상 값을 통해 최적의 행동 계획을 찾을 수 있도록 합니다. 이 알고리즘은 다양한 행동 경로를 평가하고 가장 유망한 경로를 선택하여, 탐색과 활용을 통해 에이전트의 전략을 지속적으로 개선합니다.

+ **강화학습 모델**: 상태 전환을 담당합니다. 게임 환경과 관측 데이터를 관리하며, 트리 탐색 알고리즘으로 수행된 행동을 통해 보상 값을 업데이트합니다. 강화학습 모델은 보상을 통해 환경에 적응하며, 시간이 지남에 따라 에이전트의 행동을 최적화합니다.

+ **구성 요소 간의 상호작용**: FSM은 상태와 가능한 행동의 구조를 정의합니다. 각 상태 내에서 트리 탐색 알고리즘은 최적의 행동을 탐색하고 선택하며, 강화학습 모델의 보상을 바탕으로 합니다. 강화학습 모델은 이러한 행동의 결과를 바탕으로 정책을 업데이트하여, 미래의 결정을 더 나은 방향으로 유도합니다. 이 통합된 접근 방식은 에이전트가 환경의 변화에 적응하고, 성능을 지속적으로 향상시킬 수 있도록 합니다.
