import sys
import google.generativeai as genai


# Configure API key
genai.configure(api_key="AIzaSyCQQKLp1V2GEgnHEab1fKKL6K6O5lcBXZY")

def generate(file_path):
    # Upload the PDF file using the path passed from C++ code
    uploaded_file = genai.upload_file(path=file_path)

    # Model and request setup
    model = genai.GenerativeModel("gemini-1.5-pro")

    prompt = """
    I will upload a PDF. Your task is to generate 5 multiple-choice quiz questions from it.

    Format the output as JSON with this structure:

    {
      "quiz": [
        {
          "question": "Sample question?",
          "options": ["A", "B", "C", "D"],
          "correct_answer": "B"
        }
      ],
      "error": null
    }

    If you are unable to extract meaningful questions from the PDF or if an error occurs, return the following JSON object:

    {
      "quiz": [],
      "error": "There is an issue in uploading the file."
    }

    Ensure:
    - Each question has exactly 4 options.
    - The correct answer is explicitly mentioned in the "correct_answer" field.
    - The output is valid JSON so a C++ program can process it easily.
    - Do not add extra text, only return the JSON object.
    """

    # Generate content using the uploaded file and prompt
    response = model.generate_content(
        contents=[{"file_data": {"file_uri": uploaded_file.uri}}, {"text": prompt}],
        generation_config={"temperature": 0.7, "max_output_tokens": 1024}
    )

    # Print the response text
    print(response.text)

# Check if the file path is passed as an argument
if len(sys.argv) > 1:
    file_path = sys.argv[1]  # Get the file path from command-line arguments
    generate(file_path)
else:
    print("No file path provided.")
