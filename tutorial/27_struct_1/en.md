---
title: Group Values with Structs
part: types
part-title: Small Steps V — Making Your Own Types
goal: Group Values with Structs
related-example: reference/array
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Grouping related values

### What you will learn

**struct** defines a new type grouping related values. Put a name and score together in one Player.

### Try it

@code example1.cpp

String and int are existing types; Player is a type we create. Access the values inside it with a dot, as in player.name.

The example prints Alex: 1200. A struct definition needs a ; after its closing brace.

## Storing several grouped values

### What you will learn

A type you create can also be an array element. Array<Player> holds information about several players.

### Try it

@code struct_2_example2.cpp

players[i].score is the score of player i. Reuse the method for finding a maximum's position, then print that player's name at the end.

The expected result is Winner: Mina. Change the scores and check that the winner changes.

## Exercise

Create a `Point` struct with double x and y. Store (3.5, 7.0) and print the values.

@exercise exercise1_starter.cpp

### Hint

Start with `struct Point { double x; double y; };`.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Put three Players with name and score in an Array and print the name of the Player with the highest score.

@exercise struct_2_exercise2_starter.cpp

### Hint

Use the lesson's best-index pattern.

@solution struct_2_exercise2_solution.cpp
