# SDAEP(State-Based Dynamic Action Expansion Planning Model)


> This system, inspired by Monte Carlo Tree Search (MCTS), allows an agent to dynamically expand and plan its actions based on the current state through tree expansion and selection algorithms applied to a state-based system with a reinforcement learning model.

+ **FSM**: Each state has a set of possible actions. A tree search object exists for each state, which expands and plans actions within the state. The FSM ensures that the agent's actions are organized and executed according to the current state, maintaining a structured approach to state transitions and action selections.

+ **Tree Search Algorithm**: Based on the current state, possible actions are expanded into a tree structure, selecting and executing the optimal child node. The reward values help find the optimal action plan. This algorithm evaluates different action paths and selects the most promising one, continuously refining the agent's strategy through exploration and exploitation.

+ **Reinforcement Learning Model**: Manages state transitions. It handles the game environment and observational data, updating reward values based on actions performed by the tree search algorithm. The reinforcement learning model adapts to the environment by learning from the rewards received, optimizing the agent's behavior over time.


#

</br>

> 이 시스템은 몬테카를로 트리 탐색에 영감을 받아 상태기반과 강화학습모델이 적용된 시스템에 트리 확장 및 선택 알고리즘을 통해 에이전트가 현재 상태에 기반하여 동적으로 행동을 확장하고 계획할 수 있게 합니다.

+ FSM: 상태별 가능한 행동집합이 존재합니다. 상태마다 트리탐색객체가 존재하며 이 객체를 통해 상태 내에서 행동을 확장하고 계획합니다.

+ 트리탐색알고리즘: 현재 상태에 기반하여 가능한 행동집합을 통해 행동을 트리형태로 확장하고 최적의 자식노드를 선택하고 실행해 나갑니다. 보상값을 통해 최적의 행동계획을 찾을 수 있도록 합니다. 

+ 강화학습모델: 상태의 전환을 담당합니다. 게임 환경과 관측 데이터를 관리하며 트리 탐색 알고리즘으로 수행된 행동을 통해 보상값을 업데이트합니다
