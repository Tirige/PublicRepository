package prot_skimming;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.OverlayLayout;


public class Skimming_Text_Dialog extends JDialog {

	public  Skimming_Text_Dialog(String title,int bu1,int bu2,int ko1,int ko2, String F_txt, String F_bg){

		String htmlStr;

	    Kuromoji ku = new Kuromoji();
	    //読み込んだファイル文字列に改行文字列<br>タグを仕込み　htmlStrに加える
	    htmlStr = new FileRead().FRead(F_txt);						//FReadを使いファイルを開く
	    htmlStr = ku.Kuro(htmlStr, bu1,bu2,ko1,ko2);								//Kuromojiを使い形態素解析にかける
//	    htmlStr = ku.LastArk(htmlStr);							//ラベル内の文字列位置を固定するために


		super.setTitle(title);
		super.setSize(800,500);									//ウィンドウフレームサイズの設定
		super.setLocationRelativeTo(null);						//初期画面出現位置設定 nullで中央
		super.setDefaultCloseOperation(DISPOSE_ON_CLOSE);

	    JPanel panelBase_Dia = new JPanel();
		panelBase_Dia.setLayout(null);

			//panel_text テキスト描画のためのパネル
			JPanel panel_text = new JPanel();
			CardLayout CL = new CardLayout();
			panel_text.setLayout(CL);
			panel_text.setBounds(80, 25, 620, 425);
			panel_text.setOpaque(false);							//falseで背景を透明にできる

				JLabel labelText = new JLabel(htmlStr);
				labelText.setFont(new Font("ＭＳ ゴシック", Font.BOLD, 20));
				labelText.setForeground(Color.WHITE);

			panel_text.add("lb1",labelText);


			//bg_panel 背景描写をするためのパネル
			JPanel bg_panel = new JPanel();
			bg_panel.setBounds(0, 0, 800, 500);
		    bg_panel.setLayout(new OverlayLayout(bg_panel));

		    //背景
		    //サイズ変更出力
		    	ImageIcon bg_icon = new ImageIcon(F_bg);
		    	Image bgr_Icon = bg_icon.getImage().getScaledInstance(800, 500, Image.SCALE_SMOOTH);
		    	bg_icon = new ImageIcon(bgr_Icon);
		    	JLabel  j = new JLabel(bg_icon);

		    bg_panel.add(j);


		panelBase_Dia.add(panel_text);
		panelBase_Dia.add(bg_panel);
		super.getContentPane().add(panelBase_Dia, BorderLayout.CENTER);

	}

}
