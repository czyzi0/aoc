local SOLUTIONS_PART1 = {
    ["sample1.txt"] = 11,
    ["input.txt"] = 2344935,
}
local SOLUTIONS_PART2 = {
    ["sample1.txt"] = 31,
    ["input.txt"] = 27647262,
}


local function read_lists(file_path)
    local l_list, r_list = {}, {}
    for line in io.lines(file_path) do
        local l_number, r_number = string.match(line, "(%d+)%s+(%d+)")
        table.insert(l_list, tonumber(l_number))
        table.insert(r_list, tonumber(r_number))
    end
    assert(#l_list == #r_list)
    return l_list, r_list
end


local function solve_part1(file_path)
    local l_list, r_list = read_lists(file_path)
    table.sort(l_list)
    table.sort(r_list)

    local result = 0
    for i = 1, #l_list do
        result = result + math.abs(l_list[i] - r_list[i])
    end
    return result
end


local function solve_part2(file_path)
    local l_list, r_list = read_lists(file_path)

    local result, counts = 0, {}
    for _, n in ipairs(l_list) do
        local count = counts[n]
        if not count then
            count = 0
            for _, n_ in ipairs(r_list) do
                if n == n_ then
                    count = count + 1
                end
            end
        end
        result = result + n * count
    end
    return result
end


local function solve(file_path)
    local file_name = string.match(file_path, ".*/([^/]+)")
    print("### " .. file_name .. " ###")

    if SOLUTIONS_PART1[file_name] ~= nil then
        local solution_part1_ = solve_part1(file_path)
        print("Part1: " .. solution_part1_)
        local solution_part1 = SOLUTIONS_PART1[file_name]
        assert(solution_part1_ == solution_part1)
    end

    if SOLUTIONS_PART2[file_name] ~= nil then
        local solution_part2_ = solve_part2(file_path)
        print("Part2: " .. solution_part2_)
        local solution_part2 = SOLUTIONS_PART2[file_name]
        assert(solution_part2_ == solution_part2)
    end
end


for _, file_path in ipairs(arg) do
    solve(file_path)
end
