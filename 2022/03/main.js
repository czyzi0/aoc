const assert = require('assert');
const fs = require('fs');
const path = require('path');


const SOLUTIONS_PART1 = {
  'sample1.txt': 157,
  'input.txt': 7597,
};
const SOLUTIONS_PART2 = {
  'sample1.txt': 70,
  'input.txt': 2607,
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
  const lines = fs.readFileSync(filePath, 'utf8').trim().split(/\n/);

  let solution = 0;

  for (const line of lines) {
    assert(line.length % 2 === 0);
    const compartmentL = new Set(line.slice(0, line.length / 2));
    const compartmentR = new Set(line.slice(line.length / 2, line.length));

    const intersection = compartmentL.intersection(compartmentR);
    assert(intersection.size === 1);
    const [element] = intersection;

    solution += calculatePriority(element);
  }

  return solution
}


function solvePart2(filePath) {
  const lines = fs.readFileSync(filePath, 'utf8').trim().split(/\n/);
  assert(lines.length % 3 === 0);

  let solution = 0;

  for (let i = 0; i < lines.length; i += 3) {
    const [rucksackA, rucksackB, rucksackC] = lines.slice(i, i + 3).map(r => new Set(r));

    const intersection = rucksackA.intersection(rucksackB).intersection(rucksackC);
    assert(intersection.size === 1);
    const [element] = intersection;

    solution += calculatePriority(element);
  }

  return solution;
}


function calculatePriority(element) {
  // a-z: 1-26, A-Z: 27-52
  if (/[A-Z]/.test(element)) return element.charCodeAt() - 38;
  else if (/[a-z]/.test(element)) return element.charCodeAt() - 96;
  else assert(false);
}


process.argv.slice(2).forEach(solve);
