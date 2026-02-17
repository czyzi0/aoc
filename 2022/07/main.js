const assert = require('assert');
const fs = require('fs');
const path = require('path');


const SOLUTIONS_PART1 = {
  'sample1.txt': 95437,
  'input.txt': 1390824,
};
const SOLUTIONS_PART2 = {
  'sample1.txt': 24933642,
  'input.txt': 7490863,
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
  const root = buildFileTree(filePath);

  const solve = (node) => {
    let solution = 0;
    if (node.children !== undefined) {
      if (node.size <= 100000) solution += node.size;
      for (const child of Object.values(node.children))
        solution += solve(child);
    }
    return solution
  };
  return solve(root);
}


function solvePart2(filePath) {
  const root = buildFileTree(filePath);
  const requiredSpace = 30000000 - (70000000 - root.size);

  const solve = (node) => {
    if (node.children === undefined) return Infinity;
    const childSizes = Object.values(node.children)
      .map(solve)
      .filter(size => size >= requiredSpace);
    const minChildSize = childSizes.length > 0 ? Math.min(...childSizes) : Infinity;
    if (node.size >= requiredSpace && node.size < minChildSize) return node.size;
    return minChildSize;
  };
  return solve(root);
}


function buildFileTree(filePath) {
  const root = {'children': {}};

  let curr = root;
  let match;
  for (const line of fs.readFileSync(filePath, 'utf8').trim().split(/\n/)) {
    switch (true) {
      case line.match(/\$ cd \//) !== null:
        curr = root;
        break;
      case line.match(/\$ cd \.\./) !== null:
        curr = curr.back;
        break;
      case (match = line.match(/\$ cd (?<name>[\w\.]+)/)) !== null:
        curr = curr.children[match.groups.name];
        break;
      case (match = line.match(/dir (?<name>[\w\.]+)/)) !== null:
        curr.children[match.groups.name] = {'back': curr, 'children': {}};
        break;
      case (match = line.match(/(?<size>\d+) (?<name>[\w\.]+)/)) !== null:
        curr.children[match.groups.name] = {'size': parseInt(match.groups.size)};
        break;
    }
  }

  const calculateSizes = node => {
    if (node.size !== undefined) return node.size;
    node.size = Object.values(node.children)
      .map(calculateSizes)
      .reduce((sum, val) => sum + val, 0);
    return node.size;
  };
  calculateSizes(root);

  return root;
}


process.argv.slice(2).forEach(solve);
