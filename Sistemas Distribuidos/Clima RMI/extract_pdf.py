import pypdf
import os

pdf_path = r"c:\Users\willi\OneDrive\Documentos\Faculdade\Sistemas Distribuidos\Clima RMI\RMI_ Atividade_Clima.pdf"
output_path = r"c:\Users\willi\OneDrive\Documentos\Faculdade\Sistemas Distribuidos\Clima RMI\pdf_content.txt"

def extract_text(pdf_path, output_path):
    try:
        reader = pypdf.PdfReader(pdf_path)
        text = ""
        for page in reader.pages:
            text += page.extract_text() + "\n"
        
        with open(output_path, "w", encoding="utf-8") as f:
            f.write(text)
        print(f"Successfully extracted text to {output_path}")
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    extract_text(pdf_path, output_path)
