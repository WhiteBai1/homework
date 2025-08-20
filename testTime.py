import subprocess
import matplotlib as plt
import numpy as np

def time_mergesort (data_sizes):
    times = []

    for size in data_sizes:

        process = subprocess.Popen(
            ['./mergesort'],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )

        stdout,stderr=process.communicate(input=str(size))

        if process.returncode ==0:
            try: 
                time_taken = float(stdout.strip())
                times.append(time_taken)
            except ValueError:
                print(f"解析输出失败：{stdout}")
        else:
            print(f"程序错误：{stderr}")


    return times

data_sizes = [10,100,1000,10000,50000,100000,500000,1000000]
times = time_mergesort(data_sizes)

print("\n测试结果:")
for i, time_val in enumerate(times):
    print(f"{data_sizes[i]}: {time_val:.6f} s")