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
 <li> <h5>CView 헤더</h5> </li>
 <ul>
 <li><h5>사용자의 화면에 보여주는 역할을 하기 위한 변수와 함수들이 정의되어 있다.</h5></li>
 </ul>
 
 <li> <h5>CDocument 헤더</h5></li>
 <ul>
 <li><h5>애플리케이션 내부에서 데이터를 읽고 저장하는 기능을 위한 변수와 함수들이 정의되어 있다.</h5></li>
 </ul>
</ul>
<h4> 3) 클래스 생성</h4>
<ul>
 <li> <h5>CView 클래스</h5> </li>
 <ul>
 <li><h5>애플리케이션의 클라이언트 또는 작업 영역을 나타내는 클래스로 document 안에 있는 데이터를 뷰를 통해 화면에 보일 수 있도록 하는 기저 클래스이다.</h5></li>
 <li><h5>CView 클래스로부터 상속받은 여러 가지 형태의 폼 윈도우들이 있다.</h5></li>
 <li><h5>작업 영역으로 들어오는 메시지들을 처리 할 수 있다.</h5></li>
 <li><h5>사용자뷰들은 이 CView 클래스로부터 상속받아 사용한다.</h5></li>
 </ul>
 
 <li> <h5>CDocument 클래스</h5></li>
 <ul>
 <li><h5>함수 기능을 수행하는 클래스이다.</h5></li>
 <li><h5>애플리케이션 내부에서 데이터를 읽고, 저장하는 기능을 가진 클래스로 애플리케이션이 지정한 도큐먼트의 기본 클래스이다.</h5></li>
 <li><h5>입출력을 제공하므로 데이터의 입출력에 관한 내용은 이 클래스를 사용하는 것이 좋다.</h5></li>
 <li><h5>사용자의 도큐먼트들은 이 CDocument 클래스로부터 상속받아 사용한다.</h5></li>
 </ul>
</ul>

<br>
<h4> 4) 기능(함수) </h4>
<ul>
 <li><h5>Document 클래스 안에 있는 메서드</h5></li>
<ul>
 <li><h5>OnOpenDocument 메서드: 사용자가 화면에서 파일을 열때 실행되는 기능이다. </h5></li>
 <li><h5>OnSaveDocument 메서드: 사용자가 화면에서 데이터를 저장할 때 실행되는 기능이다. </h5></li>
 <li><h5>OnFrameComb 메서드: 입력된 영상, 마스크 영상, 합성할 영상을 가지고 논리연산을 하는 기능을 한다. </h5></li>
</ul>
 <li><h5>View 클래스 안에 있는 메서드</h5></li>
<ul>
 <li><h5>OnDraw 메서드: 애플리케이션의 화면을 통해서 데이터를 보여주는 기능을 한다.</h5></li>
 <li><h5>OnFrameComb 메서드: CDocument의 OnFrameComb 함수가 기능하도록 호출하는 기능을 한다.</h5></li>
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
