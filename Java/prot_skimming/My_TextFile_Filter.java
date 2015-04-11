package prot_skimming;

import java.io.File;

import javax.swing.filechooser.FileFilter;

public class My_TextFile_Filter extends FileFilter{

	@Override
	public boolean accept(File f) {
		// TODO 自動生成されたメソッド・スタブ
		if(f.isDirectory()){
		return true;
		}
		 String ext = getExtension(f);
         if (ext != null){
             if (ext.equals("txt")){
                 return true;
             }else{
                 return false;
             }
         }
         return false;
	}

	@Override
	public String getDescription() {
		// TODO 自動生成されたメソッド・スタブ
		return "文書ファイル .txt";
	}
	 private String  getExtension(File f){
         String ext = null; 
         String filename = f.getName(); 
         //一番後ろから.までのファイル名を読み取る
         int dotIndex = filename.lastIndexOf('.');
        if ((dotIndex > 0) && (dotIndex < filename.length() - 1)){
             ext = filename.substring(dotIndex + 1).toLowerCase();
         }

         return ext;
     } 

}
