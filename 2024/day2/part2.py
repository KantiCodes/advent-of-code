

def check_diffs(vals:list):
    diffs = set(vals[i] - vals[i-1] for i in range(1, len(vals)))
    return diffs <= {1,2,3} or diffs <= {-1, -2, -3}


result = 0

with open("a.inn", "r") as f:
    while line:= f.readline():
        vals = line.strip("\n").strip("GOOD").strip("BAD").strip(" ")
        vals = vals.split()
        vals = [int(v) for v in vals]

        vals_cp_res = False
        all_possible_lists = []

        if check_diffs(vals):
            result+=1
        
        else:
            for i in range(0, len(vals)):
                vals_cp = vals[:]
                vals_cp.pop(i)
                vals_cp_res = check_diffs(vals_cp)
                if vals_cp_res == True:
                    result += 1
                    break




print(result)