import numpy as np

# 공분산 계산 코드

x = [[170, 70],
     [150,45],
     [160,55],
     [180,60],
     [170,80]]

x_meaned = x - np.mean(x, axis = 0) # x에 x 평균을 빼서 편차를 구함

# Step-2
cov_mat = x_meaned.T @ x_meaned / len(x) # 편차의 transform과 편차를 내적하여 x의 행 개수로 나눔 @는 내적을 뜻함
# cov_mat2 = np.cov(x_meaned, rowvar = False) 위와 같은 결과

# Step-3
eigen_values, eigen_vectors = np.linalg.eigh(cov_mat) # 고유 값과 고유 벡터를 가져옴

# Step-4
sorted_index = np.argsort(eigen_values)[::-1] # eigen_values를 기준으로 높은 값 순으로 정렬
sorted_eigenvalue = eigen_values[sorted_index] # 그 값을 기준으로 정렬
sorted_eigenvectors = eigen_vectors[:,sorted_index] # 그 값을 기준으로 정렬

selected_eigenvectors = sorted_eigenvectors[:,0:1] # 정렬된 고유 벡터 중 하나만 가져옴 -> 1차원으로 줄임
x_reduced = np.dot(selected_eigenvectors.T,x_meaned.T).T # 1차원으로 축소된 값 계산 방식으로 고유 벡터와 x 평균을 내적함

print("selected_eigenvectors: ", selected_eigenvectors.T)
print('x_reduced',x_reduced) # 새로운 특징 축임


# %%

# PCA 프로그래밍 전처리과정
# StandardScaler를 사용해 모든 차원이 0~1이 되도록 평균을 제거하고 단위 분산으로 스케일링하여 표준화(정규화)
# PCA를 활용해 차원 축소
# n_components는 차원의 수
# fit_transform 함수를 통해 실행

from sklearn import preprocessing

x_scaled = preprocessing.StandardScaler().fit_transform(x)

import pandas as pd
from sklearn.decomposition import PCA

pca = PCA(n_components=1) # 정규화 후 PCA 진행

pca_features = pca.fit_transform(x_scaled)


