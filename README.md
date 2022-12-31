# Virtual Memory

<html>

<head>
<meta http-equiv=Content-Type content="text/html; charset=utf-8">
<meta name=Generator content="Microsoft Word 15 (filtered)">
</head>

<div class=WordSection1>

<p class=MsoNormal><span lang=EN-US style='font-size:24.0pt'>&nbsp;</span></p>

<h2><a name="_Toc122163610"><b><span lang=EN-US style='font-size:14.0pt'>Virtual
memory</span></b></a></h2>

<p class=MsoNormal><span lang=EN-US>&nbsp;</span></p>

<p class=MsoNormal style='text-indent:5.0pt'><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>프로그램이 실행되려면 먼저 운영체제로부터</span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'> RAM </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>주소를 할당 받아 데이터를 옮겨야 한다</span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>. </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>이때 만약 운영체제가 </span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>RAM</span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>의 실제 주소를 건네 준다면 다른 프로세스가 주소 영역을 침범하여 데이터가
변질되거나</span><span lang=EN-US style='font-family:"맑은 고딕",sans-serif'>, </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>다른 악성 프로세스가 사용자의 데이터를 손쉽게 들여다 볼 수
있게 될 것이다</span><span lang=EN-US style='font-family:"맑은 고딕",sans-serif'>. </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>또한</span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>, </span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>프로그램 개발자는 실행될 때마다 달라지는 </span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>RAM </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>주소를 고려하여 프로그램을 짜야 한다</span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>. </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>이러한 상황을 방지하기 위해 모든 프로세스는 시작과 끝 주소가 같은 가상
주소를 할당 받게 된다</span><span lang=EN-US style='font-family:"맑은 고딕",sans-serif'>. </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>가상 주소는 각자 다른 물리 주소에 매핑 됨으로써 여러 프로세스가
같은 가상 주소에 접근해도 모두 다른 물리 주소를 참조하게 하여 주소 충돌을 막아 안정성과 생산성을 높일 수 있게 된다</span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>. </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>물리 주소를 가상 주소로 매핑하거나</span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>, </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>가상 주소를 물리 주소로 변환하는 역할은 </span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>Memory Management Unit(MMU)</span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>이 맡는다</span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>. </span></p>

<p class=MsoNormal style='text-indent:5.0pt'><span lang=EN-US style='font-family:
"맑은 고딕",sans-serif'>&nbsp;</span></p>

<p class=MsoNormal align=center style='text-align:center;text-indent:5.0pt'><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'><img width=500 height=412
id="그림 2" src="README.fld/image002.png"></span></p>

<p class=MsoNormal align=center style='text-align:center'><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>↑ </span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>MMU</span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>가 가상 주소를 물리 주소로 변환한다</span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>.</span><a href="#_edn1"
name="_ednref1" title=""><span class=MsoEndnoteReference><span lang=EN-US
style='font-size:8.0pt;font-family:"맑은 고딕",sans-serif'><span
class=MsoEndnoteReference><span lang=EN-US style='font-size:8.0pt;font-family:
"맑은 고딕",sans-serif'>[i]</span></span></span></span></a><span lang=EN-US
style='font-size:8.0pt;font-family:"맑은 고딕",sans-serif'>(</span><span lang=KO
style='font-size:8.0pt;font-family:"맑은 고딕",sans-serif'>네이버 블로그</span><span
lang=EN-US style='font-size:8.0pt;font-family:"맑은 고딕",sans-serif'>, n.d.)</span></p>

<p class=MsoNormal align=center style='text-align:center'><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>&nbsp;</span></p>

<p class=MsoNormal style='text-indent:5.0pt'><span lang=EN-US style='font-family:
"맑은 고딕",sans-serif'>CPU</span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>는
물리 주소를 직접 다루지 않고 항상 가상 주소로 작업을 수행하게 된다</span><span lang=EN-US style='font-family:
"맑은 고딕",sans-serif'>. MMU</span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>는
</span><span lang=EN-US style='font-family:"맑은 고딕",sans-serif'>CPU</span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>와 메모리 사이에 위치하여 </span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>CPU</span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>가 가상 주소에 접근해야 할 경우 </span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>MMU</span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>가 </span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>CPU</span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>로부터 가상 주소를 건네 받아 물리 주소로 변환한다</span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>. </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>캐시 메모리도 마찬가지로 </span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>MMU</span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>로부터 전달받은 물리 주소로 데이터를 다루게 된다</span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>.</span></p>

<p class=MsoNormal style='text-indent:5.0pt'><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>가상 메모리 기법에는 대표적으로 초기에 사용되었던 </span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>Base&amp;Bound(B&amp;B) </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>기법과 현대에 사용되는 페이징 기법이 존재한다</span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>. </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>본 과제에서는 페이징 기법을 사용하여 가상 메모리를 구현하였다</span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>.</span></p>

<p class=MsoNormal><span lang=EN-US style='font-size:14.0pt;font-family:"맑은 고딕",sans-serif'>&nbsp;</span></p>

<h2><a name="_Toc122163611"><b><span lang=EN-US style='font-size:14.0pt'>Paging</span></b></a></h2>

<p class=MsoNormal><span lang=EN-US style='font-size:14.0pt'>&nbsp;</span></p>

<p class=MsoNormal style='text-indent:5.0pt'><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>페이징은 가상 메모리 기법 중 하나로</span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>, </span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>주 메모리를 같은 크기의 여러 프레임으로 나누고 가상 메모리를 같은 크기의 페이지로 나누어 관리하는 방법이다</span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>. </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>프로세스는 </span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>Process Control Block(PCB) </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>안에 페이지 테이블을 사용하여 자신에게 할당된 페이지들을 관리한다</span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>. </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>페이징의 장점은 초기 가상 메모리 기법인 </span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>B&amp;B</span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>가 연속적인 물리 주소 매핑으로 인한 외부 파편화의 발생으로 사용하지 못하는
공간이 생겼던 것과 다르게</span><span lang=EN-US style='font-family:"맑은 고딕",sans-serif'>, </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>프레임과 페이지 단위로 관리하는 페이징 기법은 파편화 되어있는
공간에도 가상 주소를 매핑할 수 있어 비연속적인 물리 주소를 연속적인 가상 주소로 활용할 수 있게 된다</span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>.</span></p>

<p class=MsoNormal style='text-indent:5.0pt'><span lang=EN-US style='font-family:
"맑은 고딕",sans-serif'>&nbsp;</span></p>

<p class=MsoNormal align=center style='text-align:center;text-indent:5.0pt'><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'><img width=842 height=406
id="그림 1" src="README.fld/image003.png"></span></p>

<p class=MsoNormal align=center style='text-align:center'><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>↑ 외부 파편화에 의해 새로운 프로세스를 생성하지 못하는 경우</span><a
href="#_edn2" name="_ednref2" title=""><span class=MsoEndnoteReference><span
lang=EN-US style='font-size:8.0pt;font-family:"맑은 고딕",sans-serif'><span
class=MsoEndnoteReference><span lang=EN-US style='font-size:8.0pt;font-family:
"맑은 고딕",sans-serif'>[ii]</span></span></span></span></a><span lang=EN-US
style='font-size:8.0pt;font-family:"맑은 고딕",sans-serif'>(GeeksforGeeks, n.d.)</span></p>

<p class=MsoNormal align=center style='text-align:center;text-indent:4.0pt'><span
lang=EN-US style='font-size:8.0pt;font-family:"맑은 고딕",sans-serif'>&nbsp;</span></p>

<p class=MsoNormal align=center style='text-align:center;text-indent:5.0pt'><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'><img width=602 height=544
id="그림 5" src="README.fld/image004.png"></span></p>

<p class=MsoNormal align=center style='text-align:center'><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>↑ 페이징 기법은 외부 파편화가 발생하지 않는다</span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>.</span><a href="#_edn3"
name="_ednref3" title=""><span class=MsoEndnoteReference><span lang=EN-US
style='font-size:8.0pt;font-family:"맑은 고딕",sans-serif'><span
class=MsoEndnoteReference><span lang=EN-US style='font-size:8.0pt;font-family:
"맑은 고딕",sans-serif'>[iii]</span></span></span></span></a><span lang=EN-US
style='font-size:8.0pt;font-family:"맑은 고딕",sans-serif'>(Tistory, 2020)</span></p>

<p class=MsoNormal align=center style='text-align:center;text-indent:5.0pt'><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>&nbsp;</span></p>

<p class=MsoNormal style='text-indent:5.0pt'><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>하지만 페이징 기법은 할당된 프레임의 일부분만 사용하는 내부 파편화가 발생 할 수 있다</span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>. </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>예를 들어 페이지 단위가 </span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>1024bytes</span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>일 때 어떤 프로세스가 </span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>1025bytes</span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>의 메모리가 필요하다면</span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>, </span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>페이지를 </span><span lang=EN-US style='font-family:"맑은 고딕",sans-serif'>2</span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>개 할당하여 총 </span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>2048bytes</span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>를 사용하게 된다</span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>. 1byte</span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>를 위해 </span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>1024bytes</span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>를 더 할당하게 되는 것이다</span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>. </span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>페이지의 단위를 작게 하면 내부 파편화를 최소화 할 수 있지만</span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>, </span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>그만큼 총 페이지 개수가 늘어남으로써 페이지 테이블 크기와 같은 오버헤드가 증가하게 되어 효율성이 떨어지게
된다</span><span lang=EN-US style='font-family:"맑은 고딕",sans-serif'>. </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>이러한 특성을 고려하여 오늘날의 페이징 기법은 </span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>4KB</span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>에서 </span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>8KB</span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>의 페이지 단위를 사용한다</span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>.</span></p>

<p class=MsoNormal style='text-indent:5.0pt'><span lang=EN-US style='font-family:
"맑은 고딕",sans-serif'>&nbsp;</span></p>

<p class=MsoNormal align=center style='text-align:center;text-indent:5.0pt'><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'><img width=582 height=472
id="그림 8" src="README.fld/image005.png"></span></p>

<p class=MsoNormal align=center style='text-align:center'><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>↑ 내부 파편화에 의해 프레임 내부에서 낭비되는 공간이 생긴다</span><span
lang=EN-US style='font-size:8.0pt;font-family:"맑은 고딕",sans-serif'>.<a
href="#_edn4" name="_ednref4" title=""><span class=MsoEndnoteReference><span
class=MsoEndnoteReference><span lang=EN-US style='font-size:8.0pt;font-family:
"맑은 고딕",sans-serif'>[iv]</span></span></span></a>(GeeksforGeeks, n.d.)</span></p>

<p class=MsoNormal><span lang=EN-US style='font-family:"맑은 고딕",sans-serif'>&nbsp;</span></p>

<p class=MsoNormal style='text-indent:5.0pt'><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>운영체제는 프로세스의 요청에 따라 페이지를 할당하기 위해 사용 가능한 주 메모리 프레임들을 관리해야 하고</span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>, </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>가상 주소를 물리 주소로 변환하기 위해 각 프로세스 </span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>PCB</span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>의 페이지 테이블을 갖고 있어야 한다</span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>.</span></p>

<p class=MsoNormal style='text-indent:5.0pt'><span lang=EN-US style='font-family:
"맑은 고딕",sans-serif'>&nbsp;</span></p>

<p class=MsoNormal align=center style='text-align:center;text-indent:5.0pt'><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'><img width=634 height=454
id="그림 11" src="README.fld/image006.png"></span></p>

<p class=MsoNormal align=center style='text-align:center'><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>↑ 운영체제는 사용 가능한 프레임과 프로세스의 페이지 테이블을 관리한다</span><span
lang=EN-US style='font-size:8.0pt;font-family:"맑은 고딕",sans-serif'>.<a
href="#_edn5" name="_ednref5" title=""><span class=MsoEndnoteReference><span
class=MsoEndnoteReference><span lang=EN-US style='font-size:8.0pt;font-family:
"맑은 고딕",sans-serif'>[v]</span></span></span></a>(Tistory, 2020)</span></p>

<p class=MsoNormal><span lang=EN-US style='font-family:"맑은 고딕",sans-serif'>&nbsp;</span></p>

<p class=MsoNormal><span lang=EN-US style='font-size:14.0pt'>&nbsp;</span></p>

<h3 style='margin-left:50.0pt;text-indent:-20.0pt'><a name="_Toc122163612"><b><span
lang=EN-US>Page Table</span></b></a></h3>

<p class=MsoNormal><span lang=EN-US>&nbsp;</span></p>

<p class=MsoNormal style='text-indent:5.0pt'><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>페이징</span><span lang=KO> </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>기법은</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>프로세스마다</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>하나씩</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>갖고</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>있는</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>페이지</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>테이블을</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>통해</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>가상</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>주소를</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>물리</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>주소를</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>변환한다</span><span lang=EN-US>. </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>페이지</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>테이블은</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>가상</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>주소의</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>상위</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>비트들을</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>인덱스로</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>사용하여</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>프레임</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>번호를</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>저장하는</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>자료</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>구조이다</span><span lang=EN-US>. 4GB
</span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>메모리를</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>갖고</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>페이지</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>크기가</span><span
lang=KO> </span><span lang=EN-US>4KB</span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>인</span><span lang=KO> </span><span lang=EN-US>32</span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>비트</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>주소</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>체계를</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>예로</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>들면</span><span lang=EN-US>, </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>주소에서</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>상위</span><span lang=KO> </span><span
lang=EN-US>20</span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>개</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>비트</span><span
lang=EN-US>(4GB / 4KB)</span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>를</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>페이지</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>테이블의</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>인덱스로</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>사용하여</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>프레임을</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>찾고</span><span
lang=EN-US>, </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>하위</span><span
lang=KO> </span><span lang=EN-US>12</span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>개</span><span lang=KO> </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>비트</span><span lang=EN-US>(4KB)</span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>는</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>물리</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>주소의</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>오프셋으로</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>사용하여</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>물리</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>주소로</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>변환하게</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>된다</span><span lang=EN-US>. </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>이처럼</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>하나의</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>페이지</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>테이블을</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>사용해</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>물리</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>주소로</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>변환하는</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>기법을</span><span lang=KO> </span><span
lang=EN-US>One-level </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>페이징이라</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>한다</span><span
lang=EN-US>.</span></p>

<p class=MsoNormal><span lang=EN-US>&nbsp;</span></p>

<p class=MsoNormal align=center style='text-align:center'><span lang=EN-US><img
width=554 height=480 id="그림 12" src="README.fld/image007.png"></span></p>

<p class=MsoNormal align=center style='text-align:center'><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>↑ </span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>16</span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>비트 주소 체계에서 가상 주소를 물리 주소로 변환하는 과정</span><a href="#_edn6"
name="_ednref6" title=""><span class=MsoEndnoteReference><span lang=EN-US
style='font-size:8.0pt;font-family:"맑은 고딕",sans-serif'><span
class=MsoEndnoteReference><span lang=EN-US style='font-size:8.0pt;font-family:
"맑은 고딕",sans-serif'>[vi]</span></span></span></span></a><span lang=EN-US
style='font-size:8.0pt;font-family:"맑은 고딕",sans-serif'>(Crocus, n.d.)</span></p>

<p class=MsoNormal align=left style='text-align:left'><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>&nbsp;</span></p>

<p class=MsoNormal align=left style='text-align:left;text-indent:5.0pt'><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>페이지 테이블도 하나의 자료 구조 이므로 메모리에서 공간을
차지하게 된다</span><span lang=EN-US style='font-family:"맑은 고딕",sans-serif'>. </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>예시로 사용한 </span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>32</span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>비트 주소 체계에서 페이지 테이블의 크기는 페이지 테이블 엔트리 개수 </span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>2^20</span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>에 </span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>4bytes(32</span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>비트</span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>)</span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>를 곱한 </span><span lang=EN-US style='font-family:"맑은 고딕",sans-serif'>4MB</span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>가 된다</span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>. </span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>현재 필자의 컴퓨터에서 </span><span lang=EN-US style='font-family:
"맑은 고딕",sans-serif'>600</span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>개
정도의 프로세스들이 실행 중인데</span><span lang=EN-US style='font-family:"맑은 고딕",sans-serif'>,
</span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>이 프로세스들이 각각 </span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>4MB</span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>의 페이지 테이블을 갖고 있다면 총 페이지 테이블의 크기가 약 </span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>2.4GB</span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>에 달하게 된다</span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>. </span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>게다가</span><span lang=EN-US style='font-family:"맑은 고딕",sans-serif'>,
</span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>대부분의 프로세스는 페이지 테이블의
일부 엔트리만 사용하여 작업을 수행하지만</span><span lang=EN-US style='font-family:"맑은 고딕",sans-serif'>,
</span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>이런 프로세스들에게도 </span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>4MB</span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>의 페이지 테이블 할당하는 것은 너무 많은 공간을 낭비하게 된다</span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>. </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>이러한 문제점을 해결하기 위해 </span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>Two-level </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>페이징이 고안되었다</span><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>.</span></p>

<p class=MsoNormal><span lang=EN-US>&nbsp;</span></p>

<h3 style='margin-left:50.0pt;text-indent:-20.0pt'><a name="_Toc122163613"><b><span
lang=EN-US>Two-level paging</span></b></a></h3>

<p class=MsoNormal><span lang=EN-US>&nbsp;</span></p>

<p class=MsoNormal style='text-indent:5.0pt'><span lang=EN-US>Two-level </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>페이징은</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>전술한</span><span lang=KO> </span><span
lang=EN-US>One-level </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>페이징에서</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>페이지</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>테이블의</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>크기로</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>인해</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>낭비되는</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>메모리를</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>줄이기</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>위해</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>고안된</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>기법이다</span><span
lang=EN-US>. </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>페이지</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>디렉토리</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>자료구조에</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>페이지</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>테이블을</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>할당하는</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>형태로</span><span
lang=EN-US>, </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>비어</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>있는</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>엔트리는</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>페이지</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>테이블이</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>존재하지</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>않아</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>메모리를</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>차지하지</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>않는다</span><span
lang=EN-US>. Page Table </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>목차에서</span><span
lang=KO> </span><span lang=EN-US>32</span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>비트</span><span lang=KO> </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>주소</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>체계를</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>다시</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>예시로</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>든다면</span><span lang=EN-US>, </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>주소에서</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>상위</span><span lang=KO> </span><span
lang=EN-US>10</span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>비트를</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>페이지</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>디렉토리의</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>인덱스로</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>사용하고</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>중앙의</span><span
lang=KO> </span><span lang=EN-US>10</span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>비트를</span><span lang=KO> </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>페이지</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>테이블</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>인덱스로</span><span lang=EN-US>, </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>하위</span><span lang=KO> </span><span
lang=EN-US>12</span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>비트는</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>그대로</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>오프셋으로</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>사용하는</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>것이다</span><span
lang=EN-US>. </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>따라서</span><span
lang=KO> </span><span lang=EN-US>One-level </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>페이징에선</span><span lang=KO> </span><span
lang=EN-US>1KB</span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>의</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>메모리만을</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>사용하는</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>프로세스를</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>위해</span><span
lang=KO> </span><span lang=EN-US>4MB</span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>의</span><span lang=KO> </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>페이지</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>테이블이</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>필요했지만</span><span lang=EN-US>,
Two-level </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>페이징에선</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>페이지</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>디렉토리</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>크기</span><span
lang=KO> </span><span lang=EN-US>4KB, </span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>페이지</span><span lang=KO> </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>테이블</span><span lang=KO> </span><span
lang=EN-US>1</span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>개</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>크기</span><span
lang=KO> </span><span lang=EN-US>4KB</span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>로</span><span lang=KO> </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>총</span><span lang=KO> </span><span
lang=EN-US>8KB</span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>만이</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>필요하게</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>된다</span><span
lang=EN-US>.</span></p>

<p class=MsoNormal style='text-indent:5.0pt'><span lang=EN-US>&nbsp;</span></p>

<p class=MsoNormal align=center style='text-align:center'><span lang=EN-US><img
width=602 height=384 id="그림 14" src="README.fld/image008.png"></span></p>

<p class=MsoNormal align=center style='text-align:center'><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>↑ 비어 있는 페이지 디렉토리 엔트리는 페이지 테이블이 존재하지 않으므로</span></p>

<p class=MsoNormal align=center style='text-align:center'><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>메모리를 차지하지 않는다</span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>.</span><a href="#_edn7" name="_ednref7"
title=""><span class=MsoEndnoteReference><span lang=EN-US style='font-size:
8.0pt;font-family:"맑은 고딕",sans-serif'><span class=MsoEndnoteReference><span
lang=EN-US style='font-size:8.0pt;font-family:"맑은 고딕",sans-serif'>[vii]</span></span></span></span></a><span
lang=EN-US style='font-size:8.0pt;font-family:"맑은 고딕",sans-serif'>(Tistory,
2020)</span></p>

<p class=MsoNormal><span lang=EN-US>&nbsp;</span></p>

<p class=MsoNormal style='text-indent:5.0pt'><span lang=EN-US>Two-level </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>페이징은</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>물리</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>주소로</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>변환할</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>때</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>추가적인</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>단계를</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>거치므로</span><span lang=KO> </span><span
lang=EN-US>One-level </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>페이징에</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>비해</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>오버헤드가</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>크다는</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>단점을</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>가지고</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>있다</span><span
lang=EN-US>. </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>그럼에도</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>페이징에</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>필요한</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>자료</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>구조의</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>크기를</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>획기적으로</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>줄일</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>수</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>있다는</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>장점을</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>갖고</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>있어</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>오늘날</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>운영체제에서</span><span
lang=KO> </span><span lang=EN-US>Multi-level </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>페이징으로</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>단계를</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>더</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>추가하여</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>사용</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>중이다</span><span lang=EN-US>.</span></p>

<p class=MsoNormal><span lang=EN-US>&nbsp;</span></p>

<p class=MsoNormal style='text-indent:7.0pt'><span lang=EN-US style='font-size:
14.0pt'>&nbsp;</span></p>

<h2><a name="_Toc122163614"><b><span lang=EN-US style='font-size:14.0pt'>Memory
swapping</span></b></a></h2>

<p class=MsoNormal><span lang=EN-US style='font-size:14.0pt'>&nbsp;</span></p>

<p class=MsoNormal style='text-indent:5.0pt'><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>주</span><span lang=KO> </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>메모리는</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>프로세스를</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>실행하기</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>위해</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>필수적인</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>자원이지만</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>용량이</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>한정되어</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>있다</span><span lang=EN-US>. </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>따라서</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>주</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>메모리만으로는</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>효율성에</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>한계가</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>존재하게</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>되는데</span><span lang=EN-US>, </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>이를</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>극복하기</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>위해</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>주</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>메모리를</span><span lang=KO> </span><span
lang=EN-US>HDD, SSD</span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>와</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>같은</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>용량이</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>큰</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>보조</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>메모리의</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>일부</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>영역과</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>함께</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>사용하는</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>기법인</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>메모리</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>스와핑이</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>고안되었다</span><span
lang=EN-US>.</span></p>

<p class=MsoNormal style='text-indent:5.0pt'><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>메모리</span><span lang=KO> </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>스와핑은</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>페이지를</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>주</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>메모리에서</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>보조</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>메모리로</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>옮기는</span><span lang=KO> </span><span
lang=EN-US>Swap-out</span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>과</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>보조</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>메모리에서</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>주</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>메모리로</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>옮기는</span><span
lang=KO> </span><span lang=EN-US>Swap-in </span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>과정으로</span><span lang=KO> </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>이루어진다</span><span lang=EN-US>.</span></p>

<p class=MsoNormal style='text-indent:5.0pt'><span lang=EN-US>&nbsp;</span></p>

<p class=MsoNormal align=center style='text-align:center;text-indent:5.0pt'><span
lang=EN-US><img width=474 height=358 id="그림 15" src="README.fld/image009.png"></span></p>

<p class=MsoNormal align=left style='text-align:left'><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>                                   </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>↑ 메모리 스와핑</span><a href="#_edn8"
name="_ednref8" title=""><span class=MsoEndnoteReference><span lang=EN-US
style='font-size:8.0pt;font-family:"맑은 고딕",sans-serif'><span
class=MsoEndnoteReference><span lang=EN-US style='font-size:8.0pt;font-family:
"맑은 고딕",sans-serif'>[viii]</span></span></span></span></a><span lang=EN-US
style='font-size:8.0pt;font-family:"맑은 고딕",sans-serif'>(Data Science Lab, 2015)</span></p>

<p class=MsoNormal align=center style='text-align:center;text-indent:4.0pt'><span
lang=EN-US style='font-size:8.0pt;font-family:"Arial",sans-serif;color:black;
background:white'>&nbsp;</span></p>

<p class=MsoNormal style='text-indent:5.0pt'><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>주</span><span lang=KO> </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>메모리의</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>용량이</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>가득</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>찼을</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>때</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>페이지</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>교체</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>정책에</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>의해</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>몇몇</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>페이지들을</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>보조</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>메모리로</span><span lang=KO> </span><span
lang=EN-US>Swap-out </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>함으로써</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>프로세스를</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>종료하지</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>않고도</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>용량을</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>확보할</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>수</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>있게</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>된다</span><span
lang=EN-US>. </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>또한</span><span
lang=EN-US>, </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>프로세스가</span><span
lang=KO> </span><span lang=EN-US>CPU </span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>자원을</span><span lang=KO> </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>할당</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>받았지만</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>주</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>메모리가</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>아닌</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>보조</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>메모리에</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>페이지가</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>존재할</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>경우</span><span lang=KO> </span><span
lang=EN-US>Page fault </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>인터럽트를</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>실행</span><span
lang=EN-US>, </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>보조</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>메모리에서</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>해당</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>프로세스의</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>페이지들을</span><span
lang=KO> </span><span lang=EN-US>Swap-in </span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>하여</span><span lang=KO> </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>계속</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>실행하게</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>된다</span><span lang=EN-US>.</span></p>

<p class=MsoNormal style='text-indent:5.0pt'><span lang=EN-US>Swap-out </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>할</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>페이지를</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>고르는</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>페이지</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>교체</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>정책에는</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>여러가지가</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>존재하는데</span><span lang=EN-US>, </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>그</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>중</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>대표적인</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>것으로</span><span lang=KO> </span><span
lang=EN-US>Least Recently Used(LRU) </span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>알고리즘이</span><span lang=KO> </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>있다</span><span lang=EN-US>. LRU </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>알고리즘은</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>가장</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>오랫동안</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>참조되지</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>않은</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>페이지를</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>교체하는</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>정책으로</span><span lang=EN-US>, </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>많은</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>운영체제가</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>채택하고</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>있다</span><span lang=EN-US>.</span></p>

<p class=MsoNormal style='text-indent:5.0pt'><span lang=EN-US>&nbsp;</span></p>

<p class=MsoNormal align=center style='text-align:center;text-indent:5.0pt'><span
lang=EN-US><img width=728 height=226 id="그림 13" src="README.fld/image010.png"></span></p>

<p class=MsoNormal align=center style='text-align:center'><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>↑ </span><span lang=EN-US
style='font-family:"맑은 고딕",sans-serif'>LRU </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>알고리즘의 동작 방식</span><a href="#_edn9"
name="_ednref9" title=""><span class=MsoEndnoteReference><span lang=EN-US
style='font-size:8.0pt;font-family:"맑은 고딕",sans-serif'><span
class=MsoEndnoteReference><span lang=EN-US style='font-size:8.0pt;font-family:
"맑은 고딕",sans-serif'>[ix]</span></span></span></span></a><span lang=EN-US
style='font-size:8.0pt;font-family:"맑은 고딕",sans-serif'>(Medium, 2019)</span></p>

<p class=MsoNormal><span lang=EN-US>&nbsp;</span></p>

<p class=MsoNormal><span lang=EN-US style='font-size:24.0pt'>&nbsp;</span></p>

<h2><a name="_Toc122163616"><b><span lang=KO style='font-size:14.0pt;
font-family:"맑은 고딕",sans-serif'>구현</span></b></a><b><span lang=KO
style='font-size:14.0pt'> </span></b><b><span lang=KO style='font-size:14.0pt;
font-family:"맑은 고딕",sans-serif'>환경</span></b><b><span lang=KO style='font-size:
14.0pt'> </span></b><b><span lang=KO style='font-size:14.0pt;font-family:"맑은 고딕",sans-serif'>및</span></b><b><span
lang=KO style='font-size:14.0pt'> </span></b><b><span lang=KO style='font-size:
14.0pt;font-family:"맑은 고딕",sans-serif'>실행</span></b><b><span lang=KO
style='font-size:14.0pt'> </span></b><b><span lang=KO style='font-size:14.0pt;
font-family:"맑은 고딕",sans-serif'>방법</span></b></h2>

<p class=MsoNormal><span lang=EN-US style='font-size:14.0pt'>&nbsp;</span></p>

<p class=MsoNormal><span lang=KO style='font-family:"맑은 고딕",sans-serif'>운영체제</span><span
lang=EN-US> : macOS</span></p>

<p class=MsoNormal><span lang=KO style='font-family:"맑은 고딕",sans-serif'>언어</span><span
lang=KO> </span><span lang=EN-US>: C++14</span></p>

<p class=MsoNormal><span lang=KO style='font-family:"맑은 고딕",sans-serif'>컴파일러</span><span
lang=KO> </span><span lang=EN-US>: clang 14.0.0</span></p>

<p class=MsoNormal><span lang=EN-US>Makefile </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>사용하여</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>컴파일</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>가능</span><span lang=KO> </span><span
lang=EN-US>(macOS)</span></p>

<p class=MsoListParagraph style='margin-left:38.0pt;text-indent:-18.0pt'><span
lang=EN-US style='font-family:"맑은 고딕",sans-serif'>※<span style='font:7.0pt "Times New Roman"'>&nbsp;&nbsp;&nbsp;&nbsp;
</span></span><span lang=EN-US>Linux(assam </span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>서버</span><span lang=EN-US>)</span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>의</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>경우</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>컴파일은</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>가능하지만</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>바르게</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>동작하지</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>않음</span></p>

<p class=MsoNormal><span lang=KO style='font-family:"맑은 고딕",sans-serif'>소스</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>파일</span><span
lang=KO> </span><span lang=EN-US>: Makefile, main.h, main.cpp, Scheduler.h,
Scheduler.cpp, Child.h, Child.cpp, FIFO.h, FIFO.cpp RR.h, RR.cpp, MLQ.h,
MLQ.cpp, MLFQ.h, MLFQ.cpp, CFS.h, CFS.cpp</span></p>

<p class=MsoNormal><span lang=KO style='font-family:"맑은 고딕",sans-serif'>실행</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>방법</span><span
lang=KO> </span><span lang=EN-US>: ./2022_os_proj2</span><span lang=KO
style='font-family:"맑은 고딕",sans-serif'>로</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>실행</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>후</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>사용자의</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>입력에</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>따른</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>스케줄러</span><span lang=EN-US>, </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>페이징</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>레벨로</span><span lang=KO> </span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>실행</span></p>

<p class=MsoNormal><span lang=KO style='font-family:"맑은 고딕",sans-serif'>실행</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>완료</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>후</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>출력</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>파일</span><span
lang=EN-US> : &lt;</span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>스케줄러</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>이름</span><span
lang=EN-US>&gt;_&lt;</span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>페이징</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>레벨</span><span
lang=EN-US>&gt;_schedule_dump.txt</span></p>

<p class=MsoNormal><span lang=KO style='font-family:"맑은 고딕",sans-serif'>실행</span><span
lang=KO> </span><span lang=KO style='font-family:"맑은 고딕",sans-serif'>시간</span><span
lang=KO> </span><span lang=EN-US>: </span><span lang=KO style='font-family:
"맑은 고딕",sans-serif'>약</span><span lang=KO> </span><span lang=EN-US>150</span><span
lang=KO style='font-family:"맑은 고딕",sans-serif'>초</span><span lang=EN-US>(50ms *
3000 tick)</span></p>

</div>

</html>
