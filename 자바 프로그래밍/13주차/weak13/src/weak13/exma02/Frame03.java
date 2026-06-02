package weak13.exma02;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public class Frame03 extends JFrame implements ActionListener{
	private JTextField textfield;
	private JTextArea memo;
	public Frame03() {
		setTitle("메시지 보내기");
		textfield = new JTextField(30); // 넘겨주는 매개변수는 텍스트 길이를 뜻함
		memo = new JTextArea(10,30); // 넘겨주는 매개변수는 텍스트 가로 세로 길이 뜻함(행, 열)
		memo.setEditable(false); // text area에 텍스트 직접 입력 안 되게 막음
		textfield.addActionListener(this); // textfield에 이벤트 생성 (시험 무조건 나오니까 중요하게 볼 것)
		setLayout(new BorderLayout());
		add(textfield, BorderLayout.PAGE_END); // 맨 아래에 배치
		add(memo, BorderLayout.CENTER); // 중간에 배치
		pack(); // 오브젝트 크기에 창의 크기를 맞춤
		setVisible(true);
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		String s = textfield.getText(); // textfield에 text 값 가져옴
		memo.append("send:"+s+"\n"); // textarea에 텍스트 추가
		textfield.selectAll(); // textfield 선택해줌
	}
}
