package prot_skimming;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.border.LineBorder;
import javax.swing.border.TitledBorder;

public class Skimming_Conf extends JFrame implements ActionListener{


	Skimming_Text_Dialog STD;

	JButton button1;
	JButton button2;
	JButton button3;

	JTextField textfield1;
	JTextField textfield2;

	JRadioButton rb1[],rb2[];
	ButtonGroup bg1,bg2;
	//このクラスが生成(new)された際にJFrameも作られる
	public Skimming_Conf(){

		super.setTitle("Skimming Configuration");					//ウィンドウ名
		super.setSize(600,510);										//ウィンドウフレームサイズの設定
		super.setLocationRelativeTo(null);							//ウィンドウ生成位置（nullで中央）
		super.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);		//ウィンドウ×ボタン時のアクション

		JPanel panelBase = new JPanel();
		panelBase.setLayout(null);

			JLabel label1 = new JLabel("クトゥルフ神話TRPG斜め読みツール");
			label1.setFont(new Font("ＭＳ ゴシック", Font.BOLD, 26));
			label1.setBounds(60,20,540,30);							//setBounds = (初期X位置, 初期Y位置, 幅,高さ)

			//****************************************   file_panel    **********************************//
			JPanel file_panel =new JPanel();
			file_panel.setBounds(20,60,540,180);
			file_panel.setBorder(new TitledBorder(
	    		new LineBorder(Color.GRAY, 1), "ファイル設定", TitledBorder.LEFT, TitledBorder.TOP));
			file_panel.setLayout(null);

				JPanel panel1 =new JPanel();
				panel1.setBounds(20,30,490,60);
				panel1.setBorder(new TitledBorder(
					new LineBorder(Color.GRAY, 1), "文書ファイルの指定", TitledBorder.LEFT, TitledBorder.TOP));
				panel1.setLayout(null);

					textfield1 = new JTextField("./textspace/sample_Text.txt");
					textfield1.setBounds(10, 20, 400, 30);

					button1 = new JButton("設定");
					button1.setBounds(420, 20, 60, 30);
					button1.addActionListener(this);


				JPanel panel2 =new JPanel();
				panel2.setBounds(20,100,490,60);
				panel2.setBorder(new TitledBorder(
					new LineBorder(Color.GRAY, 1), "背景画像の指定", TitledBorder.LEFT, TitledBorder.TOP));
				panel2.setLayout(null);

					textfield2 = new JTextField("./background/BG1_Table.jpg");
					textfield2.setBounds(10, 20, 400, 30);

					button2 = new JButton("設定");
					button2.setBounds(420, 20, 60, 30);
					button2.addActionListener(this);


				panel1.add(textfield1);
				panel1.add(button1);
				panel2.add(textfield2);
				panel2.add(button2);


			///////////////////////////////////////////////////////////////////////////////////////////////
			//*****************************************    rand_panel  **********************************//
			JPanel rand_panel =new JPanel();
			rand_panel.setBounds(20,240,540,180);
			rand_panel.setBorder(new TitledBorder(
		    	new LineBorder(Color.GRAY, 1), "出力確率の設定", TitledBorder.LEFT, TitledBorder.TOP));
			rand_panel.setLayout(null);

				JPanel panel3 =new JPanel();
				panel3.setBounds(20,30,490,60);
				panel3.setBorder(new TitledBorder(
					new LineBorder(Color.GRAY, 1), "名詞", TitledBorder.LEFT, TitledBorder.TOP));
				panel3.setLayout(null);

					bg1 = new ButtonGroup();

					rb1 = new JRadioButton[7];
					rb1[0] = new JRadioButton("100%", false);
					rb1[0].setBounds(25, 25, 55, 20);
					rb1[1] = new JRadioButton("80%", true);
					rb1[1].setBounds(90, 25, 55, 20);
					rb1[2] = new JRadioButton("60%", false);
					rb1[2].setBounds(155, 25, 55, 20);
					rb1[3] = new JRadioButton("40%", false);
					rb1[3].setBounds(220, 25, 55, 20);
					rb1[4] = new JRadioButton("20%", false);
					rb1[4].setBounds(285, 25, 55, 20);
					rb1[5] = new JRadioButton("10%", false);
					rb1[5].setBounds(350, 25, 55, 20);
					rb1[6] = new JRadioButton("0%", false);
					rb1[6].setBounds(415, 25, 55, 20);

					bg1.add(rb1[0]);
					bg1.add(rb1[1]);
					bg1.add(rb1[2]);
					bg1.add(rb1[3]);
					bg1.add(rb1[4]);
					bg1.add(rb1[5]);
					bg1.add(rb1[6]);


				JPanel panel4 =new JPanel();
				panel4.setBounds(20,100,490,60);
				panel4.setBorder(new TitledBorder(
					new LineBorder(Color.GRAY, 1), "動詞", TitledBorder.LEFT, TitledBorder.TOP));
				panel4.setLayout(null);

					bg2 = new ButtonGroup();

					rb2= new JRadioButton[7];
					rb2[0] = new JRadioButton("100%", false);
					rb2[0].setBounds(25, 25, 55, 20);
					rb2[1] = new JRadioButton("80%", false);
					rb2[1].setBounds(90, 25, 55, 20);
					rb2[2] = new JRadioButton("60%", true);
					rb2[2].setBounds(155, 25, 55, 20);
					rb2[3] = new JRadioButton("40%", false);
					rb2[3].setBounds(220, 25, 55, 20);
					rb2[4] = new JRadioButton("20%", false);
					rb2[4].setBounds(285, 25, 55, 20);
					rb2[5] = new JRadioButton("10%", false);
					rb2[5].setBounds(350, 25, 55, 20);
					rb2[6] = new JRadioButton("0%", false);
					rb2[6].setBounds(415, 25, 55, 20);

					bg2.add(rb2[0]);
					bg2.add(rb2[1]);
					bg2.add(rb2[2]);
					bg2.add(rb2[3]);
					bg2.add(rb2[4]);
					bg2.add(rb2[5]);
					bg2.add(rb2[6]);


				panel3.add(rb1[0]);
				panel3.add(rb1[1]);
				panel3.add(rb1[2]);
				panel3.add(rb1[3]);
				panel3.add(rb1[4]);
				panel3.add(rb1[5]);
				panel3.add(rb1[6]);
				panel4.add(rb2[0]);
				panel4.add(rb2[1]);
				panel4.add(rb2[2]);
				panel4.add(rb2[3]);
				panel4.add(rb2[4]);
				panel4.add(rb2[5]);
				panel4.add(rb2[6]);


			////////////////////////////////////////////////////////////////////////////////////////////////
			button3 = new JButton("create");
			button3.setBounds(250, 430, 80, 30);
			button3.addActionListener(this);

			file_panel.add(panel1);
			file_panel.add(panel2);
			rand_panel.add(panel3);
			rand_panel.add(panel4);

		panelBase.add(label1);
		panelBase.add(file_panel);
		panelBase.add(rand_panel);
		panelBase.add(button3);

		super.getContentPane().add(panelBase, BorderLayout.CENTER);
		super.setVisible(true);								//JFrame及び内容物可視化
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO 自動生成されたメソッド・スタブ

		if(e.getSource() == button1 ){
			System.out.println("ボタン１");
			JFileChooser FC1 = new JFileChooser("./");
			FC1.addChoosableFileFilter(new My_TextFile_Filter());
			int selected = FC1.showOpenDialog(this);
		    if (selected == JFileChooser.APPROVE_OPTION){
		      textfield1.setText(FC1.getSelectedFile().getAbsolutePath());
		    }
		}
		else if(e.getSource() == button2 ){
			System.out.println("ボタン2");
			JFileChooser FC1 = new JFileChooser("./");
			FC1.addChoosableFileFilter(new My_Graphic_Filter());
			int selected = FC1.showOpenDialog(this);
		    if (selected == JFileChooser.APPROVE_OPTION){
		      textfield2.setText(FC1.getSelectedFile().getPath());
		    }
		}
		else if(e.getSource() == button3){
			int B1 = 0,B2 = 0;
			int K1 = 0,K2 = 0;
			//ラジオボタングループ１から選択されているものを出力
			for (int i = 0 ; i < bg1.getButtonCount(); i++)
			{
				if (rb1[i].isSelected()){
					if(i == 0){
						K1 = 10;
						B1 = 10;
					}else if(i == 1){
						K1 = 8;
						B1 = 10;
					}else if(i == 2){
						K1 = 6;
						B1 = 10;
					}else if(i == 3){
						K1 = 4;
						B1 = 10;
					}else if(i == 4){
						K1 = 2;
						B1 = 10;
					}else if(i == 5){
						K1 = 1;
						B1 = 10;
					}else{
						K1 = 1;
						B1 = 0;
					}
//			        System.out.println("b1 = " + B1);
				}
			}
			//ラジオボタングループ２から選択されているものを出力
			for (int i = 0 ; i < bg2.getButtonCount(); i++)
			{
				if (rb2[i].isSelected()){
					if(i == 0){
						K2 = 10;
						B2 = 10;
					}else if(i == 1){
						K2 = 8;
						B2 = 10;
					}else if(i == 2){
						K2 = 6;
						B2 = 10;
					}else if(i == 3){
						K2 = 4;
						B2 = 10;
					}else if(i == 4){
						K2 = 2;
						B2 = 10;
					}else if(i == 5){
						K2 = 1;
						B2 = 10;
					}else{

						K2 = 1;
						B2 = 0;
					}
//			        System.out.println("b2 = " + B2);
				}
			}
			if(true){
				STD = new Skimming_Text_Dialog("テキストファイルの名前",B1,B2,K1,K2,textfield1.getText(),textfield2.getText());
				STD.setModal(true);
				STD.setVisible(true);

			}

		}
	}
}
