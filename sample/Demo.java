import java.io.*;
import java.util.*;

public class Demo {

	private String name = null;
	private final int LEN = 5;
	private final int LEN1 = 50000;

	public Demo(){
		this.name = "Java";
	}

	public Demo(String name){
		this.name = name;
	}

	public String StringCall(){
		System.out.println("StringCall hello " + this.name);
		StringBuffer str = new StringBuffer(LEN1*1042);
		long j1 = System.currentTimeMillis();
		for (int i = 0; i < 50000; i++)
		{
			str.append("030000222814871TG102C13710699146             46000064217473235714005126589020141029093013d220141029094110         91003001000010    1A03020     00000000002             GC                                                 0       0       02                                                                    0                                   9 2006850289139 082000015949883                 200    4068925492 2           0                         0                         0                         0                         0                                 0                2           0                         0                         0                             031720000007     30001                                01109           0       0       00                                     2302381671504                        CMWAP                                                           ddb15303                            DDB14F02                             321         1720000007     141125    1886509       03              1                     \n");
		}
		long j2 = System.currentTimeMillis();
		System.out.println("j2 - j1 = " + (j2 - j1)/1000.0);
		return str.toString();
	}

	public int IntCall(){
		System.out.println("IntCall hello " + this.name);
		return 5;
	}

	public String[] VectorCall(){
		System.out.println("VectorCall hello " + this.name);
		String[] vs = new String[LEN];
		for (int i = 0; i < LEN; i++) {
			vs[i] = "030000222814871TG102C13710699146             46000064217473235714005126589020141029093013d220141029094110             91003001000010    1A03020     00000000002             GC                                                 0       0       0    2                                                                    0                                   9 2006850289139 0820000    15949883                 200    4068925492 2           0                         0                         0                             0                         0                                 0                2           0                         0                             0                             031720000007     30001                                01109           0       0           00                                     2302381671504                        CMWAP                                                               ddb15303                            DDB14F02                             321         1720000007     141125        1886509       03              1                     \n";		
		}
		return vs;
	}

	public ArrayList<String> ArrayListCall(){
		System.out.println("ArrayListCall hello " + this.name);
		ArrayList<String> as = new ArrayList<String>(LEN);
		for (int i = 0; i < LEN; i++) {
			as.add(new String("I am " + this.name));		
		}
		return as;
	}

	public static void readFileByLines(String fileName) {
		File file = new File(fileName);
		BufferedReader reader = null;
		try {
			reader = new BufferedReader(new FileReader(file));
			String tempString = null;
			int line = 1;
			while ((tempString = reader.readLine()) != null) {
				System.out.println("line " + line + ": " + tempString);
				line++;
			}
			reader.close();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (reader != null) {
				try {
					reader.close();
				} catch (IOException e1) {
				}
			}
		}
	}

	public static void main(String[] args) {
		Demo d = new Demo();
		String str = d.StringCall();
		System.out.println(str);

		d = new Demo("C++");
		String[] vstr = d.VectorCall();
		for (String s : vstr) {
			System.out.println(s);
		}
	}

}
