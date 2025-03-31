    #include "quizexamen.h"
    #include "ui_quizexamen.h"
    #include <QDebug>
    #include <QMessageBox>
    #include "homepage.h"

    QuizExamen::QuizExamen(User *user,Quiz *quiz, QWidget *parent)
    : QDialog(parent), ui(new Ui::QuizExamen), quiz(quiz), currentQuestionIndex(0),currentUser(user)
    {

        ui->setupUi(this);
        ui->PreviousButton->hide();
        ui->SubmitButton->hide();
        currentQuestionIndex = 0;
        std::vector<Question> questions = quiz->getQuestions();
        userAnswers = new int[questions.size()]();




        const Question& currentQuestion = questions[currentQuestionIndex];

        ui->Question->setText(currentQuestion.getText());
        ui->Answer1->setText(currentQuestion.getOptions()[0]);
        ui->Answer2->setText(currentQuestion.getOptions()[1]);
        ui->Answer3->setText(currentQuestion.getOptions()[2]);
        ui->Answer4->setText(currentQuestion.getOptions()[3]);
        connect(ui->NextButton, &QPushButton::clicked, this, [this, questions](){
            if (ui->Answer1->isChecked()) userAnswers[currentQuestionIndex] = 0;
            else if (ui->Answer2->isChecked()) userAnswers[currentQuestionIndex] = 1;
            else if (ui->Answer3->isChecked()) userAnswers[currentQuestionIndex] = 2;
            else if (ui->Answer4->isChecked()) userAnswers[currentQuestionIndex] = 3;

            currentQuestionIndex++;
            const Question& currentQuestion = questions[currentQuestionIndex];
            ui->Question->setText(currentQuestion.getText());
            ui->Answer1->setText(currentQuestion.getOptions()[0]);
            ui->Answer2->setText(currentQuestion.getOptions()[1]);
            ui->Answer3->setText(currentQuestion.getOptions()[2]);
            ui->Answer4->setText(currentQuestion.getOptions()[3]);
            if(currentQuestionIndex != 0){
                ui->PreviousButton->show();
            }else{
                ui->PreviousButton->hide();
            }
            if(currentQuestionIndex +1 == questions.size()){
                ui->NextButton->hide();
                ui->SubmitButton->show();
            }else{
                ui->NextButton->show();
                ui->SubmitButton->hide();
            }

        });
        connect(ui->PreviousButton, &QPushButton::clicked, this, [this, questions]() {

            if (ui->Answer1->isChecked()) userAnswers[currentQuestionIndex] = 0;
            else if (ui->Answer2->isChecked()) userAnswers[currentQuestionIndex] = 1;
            else if (ui->Answer3->isChecked()) userAnswers[currentQuestionIndex] = 2;
            else if (ui->Answer4->isChecked()) userAnswers[currentQuestionIndex] = 3;


            currentQuestionIndex--;
            const Question& currentQuestion = questions[currentQuestionIndex];    // Call the function to display questions when the window is shown
            ui->Question->setText(currentQuestion.getText());
            ui->Answer1->setText(currentQuestion.getOptions()[0]);
            ui->Answer2->setText(currentQuestion.getOptions()[1]);
            ui->Answer3->setText(currentQuestion.getOptions()[2]);
            ui->Answer4->setText(currentQuestion.getOptions()[3]);

            if(currentQuestionIndex == 0){
                ui->PreviousButton->hide();
            }else{
                ui->PreviousButton->show();
            }
            if(currentQuestionIndex +1 == questions.size()){
                ui->SubmitButton->show();
                ui->NextButton->hide();
            }else{
                ui->SubmitButton->hide();
                ui->NextButton->show();
            }

        });
        connect(ui->SubmitButton, &QPushButton::clicked, this, [this, questions]() {
            if (ui->Answer1->isChecked()) userAnswers[currentQuestionIndex] = 0;
            else if (ui->Answer2->isChecked()) userAnswers[currentQuestionIndex] = 1;
            else if (ui->Answer3->isChecked()) userAnswers[currentQuestionIndex] = 2;
            else if (ui->Answer4->isChecked()) userAnswers[currentQuestionIndex] = 3;

            int correctAnswers = 0;
            for (size_t i = 0; i < questions.size(); i++) {
                if (questions[i].getOptions()[userAnswers[i]] == questions[i].getCorrectAnswer()) {
                    correctAnswers++;
                }
            }
            HomePage* homePage = new HomePage(currentUser);
            homePage->show();
            this->hide();

            QMessageBox::information(homePage, "Quiz Result",
                                     QString("You got %1 out of %2 questions correct!")
                                         .arg(correctAnswers)
                                         .arg(questions.size()));
        });
    }

    QuizExamen::~QuizExamen()
    {
        delete ui;

    }


