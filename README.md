# ACM-ICPC 2017 Jakarta Regional Repository

## Repository Structure

Each problem (from A to L) has their own folder. The folder name is the `slug` of the problem, which is the codename we used when we internally prepare the problems. The following table describes the slug for each problem

| Problem Code | Problem Slug | Problem Title                     |
| ------------ | ------------ | --------------------------------- |
| A            | icpc         | Winning ICPC                      |
| B            | businessman  | Travelling Businessmen Problem    |
| C            | guess        | Non-Interactive Guessing Number   |
| D            | domino       | Make a Forest                     |
| E            | hanoi        | Parks of Jakarta                  |
| F            | random       | Random Number Generator           |
| G            | disaster     | National Disaster: Two Towers     |
| H            | tree         | ANTS                              |
| I            | country      | XEN 3166                          |
| J            | meeting      | Meeting                           |
| K            | permutation  | Permutation                       |
| L            | scarecrows   | Sacred Scarecrows                 |

In the problem folder, there should be at least the following file/folder:

- `solution.cpp`. The official solution used to generate the outputs of the testcases
- `alt-solution.cpp`. The second solution used to verify the outputs of the testcases
- `verifier.cpp`. A verifier used to validate the input of the testcases. The code will crash if the input violates the problem constraint, while it will exit gracefully and will not output anything if the input satisfies the problem constraint.
- `tc/`. A folder consisting of all testcases. The sample inputs given in the problem statement will be in the form of `<slug>_sample_<testcase number>.in/out`, while the hidden testcases will be in the form of `<slug>_<testcase number>.in/out`.
- `icpc17-<problem code in lowercase>.pdf`. The problem statement distributed to the contestants during the contest.

For the problem with multiple correct outputs for each input, there should be one more file in the problem folder:

- `scorer.cpp`. The code accepts three arguments.
  - The first parameter will be used as the filename of the input file
  - The second parameter will not be used
  - The third parameter will be used as the filename of the judge's output file
  - The contestant's output will be read from standard input
  - This code will print `WA` if the contestant's output is intended to be judged `WRONG ANSWER`, while it will not output anything if the contestants's output is intended to be judged `CORRECT`.

Other than the problem folder, there should also be a file named `icpc17-analysis.pdf` on the repository root. This consists the problem analysis which is also distributed to all contestants after the contest ended.

## Limitations

The following table describes the time limit for each problem, as broadcasted to all teams at the beginning of the contest:

| Problem Code | Problem Slug | Time Limit |
| ------------ | ------------ | ---------- |
| A            | icpc         | 1 sec      |
| B            | businessman  | 2 sec      |
| C            | guess        | 0.5 sec    |
| D            | domino       | 1 sec      |
| E            | hanoi        | 1 sec      |
| F            | random       | 2 sec      |
| G            | disaster     | 0.5 sec    |
| H            | tree         | 2 sec      |
| I            | country      | 1 sec      |
| J            | meeting      | 1 sec      |
| K            | permutation  | 3 sec      |
| L            | scarecrows   | 2 sec      |

The memory limit for all problems is 256MB, as announced in the technical briefing of the contest.

## Solutions

Note that while there are only two official published solutions, we have a lot of other solutions prepared for our internal testing. These other solutions include, but not limited to:

- Solutions in several other languages
- Solutions that is intended to be incorrect (e.g. WA, TLE, etc.)
- Other correct solutions (especially on problems with more than one correct outputs for each input)

## Errata

Note that the following announcement was broadcasted to all teams during the contest:

- Problem H: ANTS
  
  `The figures do NOT correspond to the sample case.`