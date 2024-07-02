# SDAEP(State-Based Dynamic Action Expansion Planning Model)


> This system, inspired by Monte Carlo Tree Search (MCTS), allows an agent to dynamically expand and plan its actions based on the current state through tree expansion and selection algorithms applied to a state-based system with a reinforcement learning model.

+ **FSM**: Each state has a set of possible actions. A tree search object exists for each state, which expands and plans actions within the state. The FSM ensures that the agent's actions are organized and executed according to the current state, maintaining a structured approach to state transitions and action selections.

+ **Tree Search Algorithm**: Based on the current state, possible actions are expanded into a tree structure, selecting and executing the optimal child node. The reward values help find the optimal action plan. This algorithm evaluates different action paths and selects the most promising one, continuously refining the agent's strategy through exploration and exploitation.

+ **Reinforcement Learning Model**: Manages state transitions. It handles the game environment and observational data, updating reward values based on actions performed by the tree search algorithm. The reinforcement learning model adapts to the environment by learning from the rewards received, optimizing the agent's behavior over time.


 
