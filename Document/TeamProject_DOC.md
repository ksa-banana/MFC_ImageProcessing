## [팀 프로젝트]
<h4>날짜: 2020.07.27 | 작성자: 김주연 | Version: 1.0 </h4>
<hr>
<h3> 1. 요구사항 분석 (Requirement Analysis) </h3>
<ul>
 <li><h4>논리연산을 이용한 영상 합성 프로그램</h4></li>
 <li><h4>마스크 영상을 이용하여 AND연산과 OR 연산을 구현하여 새로운 영상을 생성하고 저장한다.</h4></li>
 </ul>
<br>
<h3> 2. 구조 설계 (Structure Design)</h3>
<h4> 1) UML(Unified Modeling Language) Diagram </h4>
<h4> (1) Use Case Diagram</h4>
<img src="" width="70%" height="70%">
<h4> (2) Sequence Diagram</h4>
<img src="" width="70%" height="70%">
<h4> (3) Class Diagram</h4>
<img src="" width="70%" height="70%">
<br>
<h4> 2) 헤더 생성</h4>
<ul>
 <li> <h5>View 헤더</h5> </li>
 <ul>
 <li><h5>사용자의 화면에 보여주는 역할을 수행하는 클래스이다.</h5></li>
 </ul>
 
 <li> <h5>Document 헤더</h5></li>
 <ul>
 <li><h5>함수 기능을 수행하는 클래스이다.</h5></li>
 </ul>
</ul>
<h4> 3) 클래스 생성</h4>
<ul>
 <li> <h5>View 클래스</h5> </li>
 <ul>
 <li><h5>사용자의 화면에 보여주는 역할을 수행하는 클래스이다.</h5></li>
 </ul>
 
 <li> <h5>Document 클래스</h5></li>
 <ul>
 <li><h5>함수 기능을 수행하는 클래스이다.</h5></li>
 </ul>
</ul>

<br>
<h4> 4) 기능(함수) </h4>
<ul>
 <li><h5>Document 클래스 안에 있는 메서드</h5></li>
<ul>
 <li><h5>OnOpenDocument 메서드: </h5></li>
 <li><h5>OnSaveDocument 메서드: </h5></li>
 <li><h5>OnFrameComb 메서드: </h5></li>
</ul>
 <li><h5>View 클래스 안에 있는 메서드</h5></li>
<ul>
 <li><h5>OnDraw 메서드: 입력된 숫자(피연산자) 2개를 사용하여 덧셈한다.</h5></li>
 <li><h5>OnFrameComb 메서드: 입력된 숫자(피연산자) 2개를 사용하여 뺄샘하는 메서드(빼고자 하는 숫자에 -1을 곱하여 덧셈을 한다.)</h5></li>
</ul>

</ul>
</ul>
<br>
<hr>

<br>
<h3> 3. 입력/출력 데이터 정의 (Data Structure Design) </h3>
<ul>
 <li> <h4> 데이터 종류: BMP 영상, RAW 영상 </h4> </li>
 <li> <h4> 입력: BMP 영상, RAW 영상 (흑백 또는 컬러)</h4> </li>
 <li> <h4> 출력: BMP 영상 (픅백 또는 컬러)</h4></li>
</ul>
<br>
<br>
<hr>

<h3> 4. 알고리즘 설계 및 구현 (Algorithm Design and Implementation) </h3>
 <h4>1) Document 클래스</h4>
 <ul>
 <li><h4>OnOpenDocument 알고리즘</h4></li>
 <img src="" width="70%" height="70%">
  <li><h4>OnSaveDocument 알고리즘</h4></li>
 <img src="" width="70%" height="70%">
  <li><h4>OnFrameComb 알고리즘</h4></li>
 <img src="" width="70%" height="70%">
</ul>
<h4>2)View 클래스</h4>
<ul>
  <li><h4>OnDraw 알고리즘</h4></li>
 <img src="" width="20%" height="20%">
 <li><h4>OnFrameComb 알고리즘</h4></li>
 <img src="" width="20%" height="20%">
</ul>
<br>
<br>

<hr>
<h3> 5. 코딩 및 테스트 (Coding and Test) </h3>
<ul>
 <li><h4>결과 화면</h4></li>
  <img src="https://github.com/ksa-banana/MFC_ImageProcessing/blob/master/Image/result_capture.PNG" width="70%" height="70%">
  <li><h4>출력된 이미지</h4></li>
  <img src="https://github.com/ksa-banana/MFC_ImageProcessing/blob/master/Image/result.bmp" width="70%" height="70%">
 </ul>
