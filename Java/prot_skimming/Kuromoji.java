package prot_skimming;

import org.atilika.kuromoji.Token;
import org.atilika.kuromoji.Tokenizer;

public class Kuromoji {
	
	//文字列中の<br>の個数を17に固定する
	public String LastArk(String s){
	     String[] b = s.split("<br>");
	     System.out.println(b.length);
	     for(int i = b.length; i <18; i++){
	    	 s = s + "<br>";
	     }
	     s = s + "dadadadada";
		return s;
		
	}
	
	//呼び出した文字列から<html><br>タグ以外を形態素解析にかける(名詞、動詞、助詞、助動詞、記号)
	public String Kuro(String s,int bu1,int bu2,int ko1,int ko2){
		String RString = null;
		Tokenizer tokenizer = Tokenizer.builder().build();
		int num = 0,ran = 0;
		boolean bo = false, ht = false;
		My_Random random = new My_Random();

		 for (Token token : tokenizer.tokenize(s)) {
	           String[] features = token.getAllFeaturesArray();     	
	           ran = random.nextInt(5);	//0から4まで
	           
	           //分析結果をRStringに追加していく
	           //switch文で書けなかった
	           if(token.getSurfaceForm().equals("<") || ht)	//<html>や<br>をそのまま残すため
	           {
//	        	   System.out.println(token.getSurfaceForm());
	        	   ht = true;
	        	   if(RString == null){
	        		   RString = token.getSurfaceForm();
	        	   }
	        	   else{
	        		   RString = RString + token.getSurfaceForm();
	        	   }
	        	   if(token.getSurfaceForm().equals(">")){
	        		   ht = false;
	        	   }
	           }
	           
	           else if(features[0].equals("名詞") && random.Kakuritu(ko1, bu1))
	           {
	        	   RString = RString + token.getSurfaceForm();  
	        	   bo = true;
	           }
	           else if(features[0].equals("動詞") && random.Kakuritu(ko2, bu2))
	           {
	        	   RString  = RString + token.getSurfaceForm();
	        	   bo = true;
	           }
	           //連体詞や記号など発生しにくいものがあるので救済処置
	           else if((random.Kakuritu(ko1, bu1)&&random.Kakuritu(ko2, bu2)) && !bo &&
	        		   	!(features[0].equals("名詞") || features[0].equals("動詞"))){
	        	   
	        	   RString = RString + token.getSurfaceForm();
	        	   bo = true;
	        	   
	           }
	           else if(bo && !(features[0].equals("名詞") || features[0].equals("動詞")))
	           {
	        	   RString = RString + token.getSurfaceForm();
	        	   bo = false;
	        	   
	           }
	           else	//引っかからなかった場合に文字数分*を入れる
	           {
	        	   bo = false;
	        	   for(int i = token.getSurfaceForm().length(); i > 0; i--){
	        		   RString = RString + "＊";
	        	   }	           }	           
		 }
		 
		 return RString;
	}

}
