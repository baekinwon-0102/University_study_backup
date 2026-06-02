package weak13.exma02;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JFrame;

public class Frame02 extends JFrame{
	public Frame02() {
		setSize(300, 150);
		setLayout(new BorderLayout());                     // 레이아웃 설정(레이아웃은 클래스라 new, 괄호 필수)                            
		add(new JButton("버튼1"), BorderLayout.CENTER);     // FlowLayout은 순서대로 오브젝트 배치
		add(new JButton("버튼2"), BorderLayout.LINE_START); // GridLayout은 행과 열로 오브젝트 배치
		add(new JButton("버튼3"), BorderLayout.LINE_END);   // BorderLayout은 동서남북, 센터로 배치
		add(new JButton("버튼4"), BorderLayout.PAGE_START);
		add(new JButton("버튼5"), BorderLayout.PAGE_END);
		setVisible(true); 
	}
}
