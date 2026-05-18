package day09.tv;

public class Television {
	// 속성 채널 볼류 턴오프: 접근제한
	// 모든 값 초기화하는 생성자 정의
	// 디폴트 생성자 정의
	// set get 함수 정의
	// toString() 메서드 재정의
	private int channel;
	private int volumn;
	private boolean turnOff;
	int count = 0;
	public Television() {
		this(1, 1, false);
	}
	public Television(int c, int v, boolean t) {
		this.channel = c;
		this.volumn = v;
		this.turnOff = t;
		count ++;
	}
	
	public int getChannel() {
		return channel;
	}
	public void setChannel(int channel) {
		this.channel = channel;
	}
	public int getVolumn() {
		return volumn;
	}
	public void setVolumn(int volumn) {
		this.volumn = volumn;
	}
	public boolean isTurnOff() {
		return turnOff;
	}
	public void setTurnOff(boolean turnOff) {
		this.turnOff = turnOff;
	}
	@Override
	public String toString() {
		return "채널명:" + channel + ", 볼륨:" + volumn + ", 실행:" + turnOff;
	}
	
	
}
