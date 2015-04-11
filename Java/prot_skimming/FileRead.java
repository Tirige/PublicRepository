package prot_skimming;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;


//テキストファイルの読み込みクラス

class FileRead
{
	final static int Wake = 29;

	//コンストラクタ
	public FileRead()
	{
	}
	//test.txtファイルが存在するか確認
	public String FRead(String tx_dir)
	{
		String htmlStr = "<html>";
		String str;						//ファイルから行単位で文字列を引き出すために使用					//
		int num = 0;

		try
		{
			File file = new File(tx_dir);

			if (checkBeforeReadfile(file))	//ファイルが存在するか確認
			{
//				System.out.println("ファイルを発見しました");


				FileInputStream fis = new FileInputStream(file);
				InputStreamReader in = new InputStreamReader(fis,"UTF-8");
				BufferedReader br = new BufferedReader(in);



				//テキストファイルをStringに落とし込む
				while((str = br.readLine()) != null){
					num = (str.length()/Wake);
					for(int i = 0; i < num; i++){
						if(i != num)
						{
							htmlStr = htmlStr + str.substring((Wake * i), Wake * (i+1))+"<br>";
						}
					}
					//最後の一行
					htmlStr = htmlStr + str.substring(Wake * num) + "<br>";

				}
				br.close();

			}else{//ファイルが開けなかった場合
				System.out.println("ファイルが見つからないか開けません");
			}
		}catch(FileNotFoundException e){
			System.out.println(e);
		}catch(IOException e){
			System.out.println(e);
		}

		return (htmlStr);	//<html>付の文章を返す

	}

	private static boolean checkBeforeReadfile(File file)
	{
		if (file.exists())
		{
			if (file.isFile() && file.canRead())
			{
				return true;
			}
		}
    return false;
	}
}
