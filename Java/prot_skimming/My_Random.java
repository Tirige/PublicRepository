package prot_skimming;

import java.util.Random;

public class My_Random extends Random{
	public My_Random(){
		
	}
	
	public boolean Kakuritu(int bunshi, int bunbo){
		int pase;
		if(bunbo == 0){
			return false;
		}
		pase = super.nextInt(bunbo) + 1;
//		System.out.println("分子 / 分母 分母高でtrue = " + (bunbo - bunshi) +" / "+ pase );
		if((bunbo - bunshi) < pase){
			System.out.println("true");
			return  true;
		}
		else{
			System.out.println("false");
			return false;
		}
		
		
	}

}
