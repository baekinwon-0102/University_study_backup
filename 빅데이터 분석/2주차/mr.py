from mrjob.job import MRJob # python으로 MapReduce를 구현하기 위한 module
from mrjob.step import MRStep #  mapper와 reduce의 단계 정의
# 각 userID별 평가한 영화의 수 집계
class CountRating(MRJob):
    # map reduce의 단계(MRStep)를 정의한다. 
    def steps(self):
        return[MRStep(mapper = self.map_get_ratings,
                      reducer = self.reduce_count_ratings)]
    # mapper와 reducer 역할을 하는 method는 이전 단계가 전달하는 값을 받는다.
    # 아래 mapper는 line(u.data 하나의 line)을 전달받는다.
    def map_get_ratings(self,_,line):
        (userID,movieID,rating,timeStamp) = line.split('\t') # \t을 기준으로 값을 분리
        # key: rating, value: 1
        yield rating,1
        # return은 수행 시, 함수 종료
        # yield는 수행 후, 재시작
    # 아래 reducer는 mapper로부터 key(rating), value(1)을 전달받는다.
    def reduce_count_ratings(self,key,value):
        yield key,sum(value)
        
if __name__ == '__main__':
    CountRating.run()