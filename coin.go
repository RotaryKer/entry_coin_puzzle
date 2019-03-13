package main

import "fmt"

const (
	B = iota
	W
	S
	SIZE = 14
)

type Board [SIZE]int
type Map map[Board]int
type State struct {
	board Board
	prev  *State
}

func newState(board *Board, state *State) *State {
	st := new(State)
	st.board = *board
	st.prev = state

	return st
}
func moveStone(state *State, dest int, from int) *State {
	st := newState(&state.board, state)
	temp := st.board[dest]
	st.board[dest] = st.board[from]
	st.board[from] = temp

	//	fmt.Println(st.board)
	return st
}
func check(que []*State, st *State, m Map) bool {
	if m[st.board] == 1 {
		return false
	} else {
		m[st.board] = 1
		return true
	}
}

func answer(state *State) {
	if state != nil {
		answer(state.prev)
		fmt.Println(state.board)
	}
}

func main() {
	start := Board{S, S, W, W, W, W, S, S, B, B, B, B, S, S}
	goal := Board{S, S, B, B, B, B, S, S, W, W, W, W, S, S}
	m := make(Map)
	m[start] = 1
	que := make([]*State, 0)
	que = append(que, newState(&start, nil))
	for cnt := 0; ; cnt++ {
		state := que[cnt]
		for i := 0; i < SIZE-1; i++ {
			if i == 0 || i == 7 {
				if state.board[i] == S && (state.board[i+1] == B || state.board[i+1] == W) {
					st := moveStone(state, i, i+1)
					if goal == st.board {
						answer(st)
						fmt.Println("Finish", len(que))
						return
					}
					if check(que, st, m) {
						que = append(que, st)
					}
				}
			} else if i == 2 || i == 11 {
				if state.board[i] == S {
					if state.board[i-1] == B || state.board[i-1] == W {
						st := moveStone(state, i, i-1)
						if goal == st.board {
							answer(st)
							fmt.Println("Finish", len(que))
							return
						}
						if check(que, st, m) {
							que = append(que, st)
						}
					}
					if state.board[i+1] == B || state.board[i+1] == W {
						st := moveStone(state, i, i+1)
						if goal == st.board {
							answer(st)
							fmt.Println("Finish", len(que))
							return
						}
						if check(que, st, m) {
							que = append(que, st)
						}
					}
					if i == 2 {
						if state.board[i+9] == B || state.board[i+9] == W {
							st := moveStone(state, i, i+9)
							if goal == st.board {
								answer(st)
								fmt.Println("Finish", len(que))
								return
							}
							if check(que, st, m) {
								que = append(que, st)
							}
						}
					} else {
						if state.board[i-9] == B || state.board[i-9] == W {
							st := moveStone(state, i, i-9)
							if goal == st.board {
								answer(st)
								fmt.Println("Finish", len(que))
								return
							}
							if check(que, st, m) {
								que = append(que, st)
							}
						}
					}
				}
			} else if i == 6 || i == 13 {
				if state.board[i] == S && (state.board[i-1] == B || state.board[i-1] == W) {
					st := moveStone(state, i, i-1)
					if goal == st.board {
						answer(st)
						fmt.Println("Finish", len(que))
						return
					}
					if check(que, st, m) {
						que = append(que, st)
					}
				}
			} else {
				if state.board[i] == S && (state.board[i-1] == B || state.board[i-1] == W) {
					st := moveStone(state, i, i-1)
					if goal == st.board {
						answer(st)
						fmt.Println("Finish", len(que))
						return
					}
					if check(que, st, m) {
						que = append(que, st)
					}
				}
				if state.board[i] == S && (state.board[i+1] == B || state.board[i+1] == W) {
					st := moveStone(state, i, i+1)
					if goal == st.board {
						answer(st)
						fmt.Println("Finish", len(que))
						return
					}
					if check(que, st, m) {
						que = append(que, st)
					}
				}

			}

		}
		//fmt.Println(len(que))
	}
}
