package weak13.exma02;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class Event01 extends JFrame implements ActionListener{
	private JLabel label;
	private JButton button;
	int count = 0;
	public Event01() {
		setSize(250,150); // 프레임 사이즈
		setTitle("카운트증가"); // 프로그램 제목
		JPanel pannel = new JPanel(); // 패널
		label = new JLabel("현재카운트="+count); // 텍스트 라벨
		button = new JButton("증가"); // 버튼
		button.addActionListener(this); // 버튼 눌렀을 때 이벤트 추가
		pannel.add(label); // 패널에 오브젝트 추가
		pannel.add(button);
		add(pannel); // 프레임에 패널 추가
		setVisible(true); // 프레임 보이기
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		count++;
		label.setText("현재카운트="+count); // label text 변경, label 텍스트 받아오는건 getText
	}
	
	
}
