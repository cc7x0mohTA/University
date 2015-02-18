import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.Serializable;
import java.util.Scanner;

import javax.swing.*;

public class EdytorCzasopisma extends JFrame implements ActionListener, Serializable
{
	private static final long serialVersionUID = 1L;
	public JButton ButtonZapisz, ButtonOtworz;
	public JTextField TextTytul, TextAutor, TextRok;
	public Czasopismo K;

	public EdytorCzasopisma(String s)
	{
		initUI();  K = new Czasopismo();
		
		if(s != "")
		{
			File file = new File(s);
			ReadFromFile(file);
		}
	}

	public void ReadFromBook()
	{
		TextTytul.setText(K.Tytul);
		TextAutor.setText(K.autor);
		TextRok.setText(Integer.toString(K.wydanie));
	}
	
	public void WriteToBook()
	{
		K = new Czasopismo(TextTytul.getText(), TextAutor.getText(), Integer.parseInt(TextRok.getText()));
	}
	
	public final void initUI()
	{
		ButtonZapisz = new JButton("Zapisz do pliku");
		ButtonOtworz = new JButton("Otwórz z pliku");

		ButtonZapisz.setBounds(0, 10, 200, 30);
		ButtonOtworz.setBounds(0, 50, 200, 30);
		
		this.setLayout(null);
		
        getContentPane().add(ButtonZapisz);
        getContentPane().add(ButtonOtworz);
        ButtonZapisz.addActionListener(this);
        ButtonOtworz.addActionListener(this);
        
		TextTytul = new JTextField("Tytul");
		TextTytul.setBounds(200, 10, 200, 30);
		getContentPane().add(TextTytul);
		
		TextAutor = new JTextField("Autor");
		TextAutor.setBounds(200, 50, 200, 30);
		getContentPane().add(TextAutor);
		
		TextRok = new JTextField("Rok Wydania");
		TextRok.setBounds(200, 90, 200, 30);
		getContentPane().add(TextRok);
		
        setSize(500, 250);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }
	
	public void SaveToFile(File file)
	{
		try
		{
			PrintWriter zapis = new PrintWriter(file);
			WriteToBook();
			zapis.println(K.toString());
			zapis.close();
		}
		catch (FileNotFoundException e1) {}
	}
	
	public void ReadFromFile(File file)
	{
		try
		{
			Scanner in = new Scanner(file);
			
			String T = in.nextLine();
			String A = in.nextLine();
			String R = in.nextLine();
			
			K = new Czasopismo(T,A,Integer.parseInt(R));
			ReadFromBook();
			in.close();
		}
		catch (FileNotFoundException e1) {}
	}
	
	public void actionPerformed(ActionEvent e)
	{
		Object source = e.getSource();
		
		if( source == ButtonZapisz )
		{
			JFileChooser fileChooser = new JFileChooser();
			if (fileChooser.showSaveDialog(ButtonZapisz) == JFileChooser.APPROVE_OPTION)
			{
				File file = fileChooser.getSelectedFile();
				SaveToFile(file);
			}
		}
		
		if( source == ButtonOtworz )
		{
			JFileChooser fileChooser = new JFileChooser();
			
			if (fileChooser.showOpenDialog(ButtonOtworz) == JFileChooser.APPROVE_OPTION)
			{
				File file = fileChooser.getSelectedFile();
				ReadFromFile(file);
				
			}
		}
	}
}
