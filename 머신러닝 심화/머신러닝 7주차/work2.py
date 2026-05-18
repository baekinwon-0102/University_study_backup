import numpy as np
import random
import copy # 2차원 배열 복사하기 위한 라이브러리

pop_size = 10 # 염색체 개수
chromosome_size = 4 # 염색체의 유전자 개수

bina=[] # 2진수 10진수로 변한 위한 배열
for i in range(chromosome_size-1,-1,-1):
    bina.append(2**i)

# initialize (초기화)
pop = [] # 염색체 배열
for i in range(pop_size):
    chromosome = [] # 유전자 배열
    for j in range(chromosome_size):
        gene = random.randint(0,1) # 0~1 사이의 수 (0 또는 1)
        chromosome.append(gene) 
    pop.append(chromosome)
    
#%%
    
# fittness

pop_ten = []
for i in range(pop_size):
    ten = []
    for j in range(chromosome_size):
        ten.append(pop[i][j]*bina[j]) # 2진수를 10진수로 변환
    pop_ten.append(ten)
fitness = np.sum(pop_ten,1) # 각각의 개별 유전자의 총 합(적합도)
fitness_old = fitness

# selection(선택)
fitness_sort = np.sort(fitness)[::-1] # fitness변수(적합도)를 내림차순으로 정렬함
sorted_index = np.argsort(fitness)[::-1] # 적합도를 기준으로 내림차순 정렬한 것의 인덱스 번호 가져옴
pop_sort = [pop[i] for i in sorted_index] # 인덱스 번호를 기준으로 염색체 배열 내림차순 정렬

pop_survive = pop_sort[:4] # 살아남은 4개의 염색체

# cross over(교차)
pop_co = [] # 교차 후 염색체 배열
for i in range(pop_size):
    chromosome_selected1 = random.choice(pop_survive) # 살아남은 4개의 염색체 배열 중 하나를 가져옴
    chromosome_selected2 = random.choice(pop_survive) # 살아남은 4개의 염색체 배열 중 하나를 가져옴
    chromosome = [] # 자식 유전자 배열
    for j in range(chromosome_size):
        gene_selected = random.choice([chromosome_selected1[j],chromosome_selected2[j]]) # 두 염색체 배열의 j 번째 인덱스 값 중 하나 랜덤 선택
        chromosome.append(gene_selected)
    pop_co.append(chromosome)

pop_co_ten = []
for i in range(pop_size):
    ten = []
    for j in range(chromosome_size):
        ten.append(pop_co[i][j]*bina[j])
    pop_co_ten.append(ten)
fitness_co = np.sum(pop_co_ten,1)

# mutation(변이)
pop_mu = copy.deepcopy(pop_co) # 교차한 염색체 배열을 복사
for i in range(pop_size):
    for j in range(chromosome_size):
        if random.random() < 0.1: # 무작위로 만든 0~1사이의 실수가 0.1보다 작다면 실행 ( 이 조건문이 실행 될 확률이 10% )
            if pop_mu[i][j] == 0: # 염색체 배열 내 유전자를 변이시킴
                pop_mu[i][j] = 1
            else:
                pop_mu[i][j] = 0
                 
#%% 
   
# 종료 조건 판단
pop_mu_ten = []
for i in range(pop_size):
    ten=[]
    for j in range(chromosome_size):
        ten.append(pop_mu[i][j]*bina[j])
    pop_mu_ten.append(ten)
fitness_mu = np.sum(pop_mu_ten,1) # 변이 후 적합도

diff = fitness_mu - fitness_old # 변이 후 적합도에 기존 적합도를 빼서 적합도의 변화 확인
improve = diff.mean() # 적합도 차의 평균( 0에 수렴할 수록 좋아진다 볼 수 있음 )
print(improve)
pop = pop_mu # 기존 염색체 배열을 변이 후 염색체 배열로 초기화