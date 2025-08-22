import subprocess
import numpy as np
import matplotlib.pyplot as plt

class test_sort:
    def __init__(self,exe_path:str ='./test'):
        self.executable_path = exe_path

    def generate_test_configs(self):
        sort_funcs = ['mergesort','heapsort','quicksort']
        data_funcs = ['randomdata','sortdata','reversedata']
        scales =[10,100,1000,10000,50000,100000,500000,1000000]

        test_configs =[
            {
            'sort_func':sort_func,
            'data_func': data_func, 
            'scale': scale, 
            'repeat_times': 1 if data_func in ['sortdata','reversedata'] else 100
            }
            for sort_func in sort_funcs
            for data_func in data_funcs
            for scale in scales
        ]

        return test_configs
    
    def run_test(self,test_configs:list[dict[str,any]])->list[dict[str,any]]:
        results=[]

        for config in test_configs:
            try:
                result = subprocess.run(
                    [
                        self.executable_path,
                        config['sort_func'],
                        config['data_func'],
                        str(config['scale']),
                        str(config['repeat_times'])
                    ],
                    capture_output=True,
                    text= True,
                    timeout=180
                )
                if result.returncode ==0:
                    runtime = float(result.stdout.strip())
                    results.append({**config, 'runtime': runtime})
                    print(f"{result}")
                else:
                    print(f"{config} error:{result.stderr}")

            except Exception as e:
                print(f"{config} input error:{e}")
            
        return results
    


if __name__ == "__main__":
    tester = test_sort('./test')
    test_configs = tester.generate_test_configs()
    results = tester.run_test(test_configs)