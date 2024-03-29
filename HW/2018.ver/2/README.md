# KMP와 Boyer-Moore 알고리즘 성능 비교

## 개요
두가지 스트링 정렬 알고리즘인 **KMP와 Boyer-Moore(BM)** 알고리즘을 구현해보고 비교 분석 한다. 

두 알고리즘은 모두 C++을 이용하여 구현하였고 두 알고리즘의 데이터 셋으로는 주어진 RFC2616을 이용하였다. 

KMP 알고리즘과 BM 알고리즘은 찾을 문자열을 한 칸 한 칸 비교하지 않고 비교할 필요가 없는 부분을 비교하지 않도록 만들어 놓은 알고리즘이다. 

먼저 KMP 알고리즘은 Suffix를 이용하여 비교할 필요 없는 부분을 없앤 알고리즘이다.  

이는 비교할 패턴을 문자열의 맨 앞에 위치 시키고 오른쪽으로 비교를 하며 일치하지 않는 부분을 찾아 

이때 넘어갈 index의 배열을 만들어 이를 통해 문자열을 검색 할 때 필요 없는 부분을 제거하고 검색한다. 

BM 알고리즘은 문자열의 가장 마지막부터 비교를 해서 나오는 특성을 이용해 필요 없는 부분을 제거한다. 

문자열의 첫 자리에 비교할 pattern을 놓고 pattern의 뒤에서부터 비교하여 틀린 부분이 나오면 그만큼의 문자열 길이만큼 skip한다. 



## 상세 설계내용
### KMP 알고리즘
- KMP 알고리즘은 책에 있는 알고리즘을 참조하여 만들어주었다. (according to the sudo code from text book)
- 주어진 text파일을 읽을 때는 루프문을 이용하여 get함수로 읽어주었고 pattern입력은 띄어쓰기 인식을 위해 getline을 이용해 읽어주었다. 
- 시간의 측정은 저번 과제와 마찬가지로 time 헤더에 있는 clock 함수를 이용하였다. 
- Text 파일을 저장할 배열의 크기는 넉넉하게 10만으로 잡아주었다. (RFC2616의 크기는 5만 이상이었다.) 
- pattern의 길이는 100으로 잡아주었다. 
- Text와 pattern 배열을 둘다 동적할당으로 설정해주었다.


### BM 알고리즘
- BM 알고리즘은 KMP 알고리즘와 마찬가지로 책의 알고리즘을 참조하였다. 
- 하지만 책의 경우는 대문자만 인식 가능하도록 선언되었으므로 띄어쓰기와 특수 함수 및 소문자 인식을 위해 수정하였다. 
- KMP와 마찬가지로 get함수로 텍스트 파일을 getline 함수로 pattern을 읽어주었고 크기는 각각 10만과 100으로 설정해주었다. 
- 측정은 저번 과제와 마찬가지로 time 헤더에 있는 clock 함수를 이용하였다. 



## 분석 및 결론

**비교 분석을 위해 워드 파일에서도 검색을 진행하였다.**

비교할 pattern은 적절한 개수를 가지는 단어와 띄어쓰기 및 특수문자를 포함한 단어, 그리고 문자열을 선택하였다. 또한 대소문자 구분이 가능한지 비교해보았다.

### 1) Purpose | purpose
먼저 대소문자 구분이 확인 가능한지 Purpose와 purpose를 검색해서 확인해보았다. word에서 검색 결과 총 8개의 검색 결과가 나왔는데 word는 대소문자 구분을 안 하므로 8개가 나왔고 실제로 확인해보면 Purpose는 1개 purpose는 7개가 나왔다.
KMP와 BM에서 검색해본 결과 KMP에서 Purpose는 1ms purpose는 4ms가 걸렸고 BM에서 는 1ms와 2ms가 걸렸다. 

### 2)  yes | no
이번에는 특수문자 및 띄어쓰기 확인을 위해 yes | no를 검색해보았다. 검색 결과 KMP에서는 1ms가 BM에서 역시 1ms가 걸렸다.

### 3)  An HTTP request message, as defined in section 5.
이번에는 문장 확인을 해보았다. 검색 결과 KMP에서는 2ms가 BM에서는 1ms가 걸렸다.

### Conclusion
위의 결과들을 토대로 분석해본 결과 일반적인 단어를 검색할 때는 KMP와 BM모두 크게 차이 나지 않고 대략 1ms정도의 시간이 걸렸다. 

그리고 단어의 길이가 길어질수록 빈도수가 올라갈 수록 KMP는 BM과 차이를 보였다. 

BM은 단어의 길이가 길어져도 증가의 폭이 적은 반면 KMP는 단어의 길이가 길어질수록 증가의 폭이 올라갔다.

또한 두 알고리즘 모두 빈도수가 올라갈수록 소요시간이 증가함을 보여주었다. 

단어의 길이가 길어질수록 KMP는 전처리 패턴이 늘어나고 비교해야 할 항목이 소요시간이 늘어나지만

BM은 단어의 길이가 길어질수록 일치하지 않는 경우 건너 뛸 수 있는 범위가 늘어나므로 BM은 시간이 적게 걸리고 KMP는 오래 걸린다. 

검색 결과 약 2배 정도 차이가 났다.

빈도수에 따라 소요시간이 증가한 이유는 출력하는 시간 때문이다. 
   


_in 2018 April_
