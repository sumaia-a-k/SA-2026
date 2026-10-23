"""
A small demo of the word ladder problem. There is no search algorithm yet.
We only check that the state, the action and the goal test work.

How to run (inside the SA-2026/python folder, NOT its parent folder):
    python -m sa2026.problems.wordladder.word_ladder_demo
There is no compile step: Python always runs the newest code.
"""
from sa2026.core.problem import Problem
from sa2026.core.state import State
from sa2026.problems.wordladder.word_dictionary import WordDictionary
from sa2026.problems.wordladder.word_ladder_problem import WordLadderProblem


def main():
    problem = WordLadderProblem("cat", "dog", WordDictionary.three_letter_words())
    start = problem.get_initial_state()

    print("=== Initial state ===")
    print(start)
    print(f"Is it a goal? {problem.is_goal(start)}")

    # one action, many next states
    print("\n=== Next states of the initial state ===")
    for action in problem.get_actions():
        print(f"{action.get_name()}: {action.apply(start)}")

    # walk by hand to the goal (this is not the shortest ladder; can you find a shorter one?)
    print("\n=== Walk by hand to the goal ===")
    path = ["hat", "hot", "dot", "dog"]
    current = start
    print(current, end="")  # end="" = do not go to a new line
    for word in path:
        current = move_to(problem, current, word)
        if current is None:
            print(f'\nStopped: can not go to "{word}" from here.')
            return
        print(f" -> {current}", end="")
    print(f"\nIs it a goal? {problem.is_goal(current)}")


# applies the actions and picks the next state with this word (or None)
def move_to(problem: Problem, state: State, word: str) -> State | None:
    for action in problem.get_actions():
        next_states = action.apply(state)
        for next_state in next_states:
            if str(next_state) == word:
                return next_state
    return None


# run main() only when this file is started, not when another file imports it
if __name__ == "__main__":
    main()
