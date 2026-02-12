const assert = require('assert');
const fs = require('fs');
const path = require('path');


const SOLUTIONS_PART1 = {
  'sample1.txt': 'CMZ',
  'input.txt': 'WCZTHTMPS',
};
const SOLUTIONS_PART2 = {
  'sample1.txt': 'MCD',
  'input.txt': 'BLSGJSDTS',
};


function solve(filePath) {
  const fileName = path.basename(filePath)
  console.log(`### ${fileName} ###`)

  if (fileName in SOLUTIONS_PART1) {
    const solutionPart1_ = solvePart1(filePath);
    console.log(`Part 1: ${solutionPart1_}`);
    const solutionPart1 = SOLUTIONS_PART1[fileName];
    assert(solutionPart1_ === solutionPart1);
  }

  if (fileName in SOLUTIONS_PART2) {
    const solutionPart2_ = solvePart2(filePath);
    console.log(`Part 2: ${solutionPart2_}`);
    const solutionPart2 = SOLUTIONS_PART2[fileName];
    assert(solutionPart2_ === solutionPart2);
  }
}


function solvePart1(filePath) {
  const { stacks, moves } = loadInput(filePath);
  for (const move of moves) {
    for (let i = 0; i < move.amount; ++i) {
      stacks[move.to].push(stacks[move.from].pop());
    }
  }
  return stacks.map(s => s.pop()).join('');
}


function solvePart2(filePath) {
  const { stacks, moves } = loadInput(filePath);
  for (const move of moves) {
    stacks[move.to].push(...stacks[move.from].splice(-move.amount));
  }
  return stacks.map(s => s.pop()).join('');
}


function loadInput(filePath) {
  const [stackLines, moveLines] = fs.readFileSync(filePath, 'utf8')
    .replace(/\s*$/, '')
    .split(/\n\n/)
    .map(x => x.split(/\n/));

  const nStacks = parseInt(stackLines.pop().trim().split(/\s+/).pop());
  const stacks = Array(nStacks).fill().map(() => []);
  while (stackLines.length > 0) {
    let i = 0;
    for (const match of stackLines.pop().matchAll(/(?:\[(\w)\]|   )(?: |$)/g)) {
      if (match[1] !== undefined) stacks[i].push(match[1]);
      i++;
    }
  }

  const moves = moveLines.map(l => {
    const match = l.match(/move (\d+) from (\d+) to (\d+)/);
    return {
      'amount': parseInt(match[1]),
      'from': parseInt(match[2]) - 1,
      'to': parseInt(match[3]) - 1,
    };
  });

  return {'stacks': stacks, 'moves': moves};
}


process.argv.slice(2).forEach(solve);
