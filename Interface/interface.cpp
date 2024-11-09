#include "interface.h"
#include "ui_interface.h"
#include "common.h"
#include <iostream>

using namespace std;

void Interface::clear_face()
{
    ui->x_label->hide();
    ui->an_label->hide();
    ui->re_edit->hide();
    ui->re_edit->setText("0");
    ui->im_edit->hide();
    ui->im_edit->setText("0");
    ui->i_label->hide();
    ui->eprint_box->hide();
    ui->size_label->hide();
    ui->new_size_edit->hide();
    ui->new_size_edit->setText("0");
    ui->polin_num_label->hide();
    ui->polin_text_label->hide();
    ui->an_label_2->hide();
    ui->index_change_label->hide();
    ui->index_change_edit->hide();
    ui->index_change_edit->setText("1");

}

Interface::Interface(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Interface)
{
    ui->setupUi(this);
    prev_butt = 0;

    size = 2;
    /*number a_n(3, 0);
    number n_roots[] = {number(3, 0), number(2, 0), number(1, 0)};
    polin.change_size(3);
    polin.change_an(a_n);
    polin.change_roots(n_roots[0], 0);
    polin.change_roots(n_roots[1], 1);
    polin.change_roots(n_roots[2], 2);
    polin.change_print_mode(PrintModeClassic);*/

    clear_face();
}

Interface::~Interface()
{
    delete ui;
}

void Interface::on_change_an_but_clicked()
{
    clear_face();

    prev_butt = 1;
    ui->an_label_2->show();
    ui->an_label->show();
    ui->im_edit->show();
    ui->re_edit->show();
    ui->i_label->show();
}


void Interface::on_enter_X_but_clicked()
{
    clear_face();

    prev_butt = 2;

    ui->x_label->show();
    ui->im_edit->show();
    ui->re_edit->show();
    ui->i_label->show();
}


void Interface::on_enter_pol_but_clicked()
{
    clear_face();

    prev_butt = 3;
    //ui->an_label_2->show();
    //ui->polin_num_label->show();
    //ui->polin_text_label->show();
    ui->polin_text_label->show();
    ui->polin_num_label->show();
    ui->an_label->show();
    ui->im_edit->show();
    ui->re_edit->show();
    ui->i_label->show();
}



void Interface::on_change_print_but_clicked()
{
    clear_face();

    prev_butt = 4;

    ui->eprint_box->show();
}


void Interface::on_change_len_but_clicked()
{
    clear_face();

    prev_butt = 5;

    ui->new_size_edit->show();
    ui->size_label->show();
}

void Interface::on_index_change_buttom_clicked()
{
    clear_face();

    prev_butt = 6;
    ui->re_edit->show();
    ui->im_edit->show();
    ui->i_label->show();
    ui->index_change_edit->show();
    ui->polin_text_label->show();
}


void Interface::on_do_but_clicked()
{

    QString msg;

    if(prev_butt == 1)
    {
        msg << QString().setNum(CHANGE_AN_REQUEST);
        msg << ui->re_edit->text() << ui->im_edit->text();
        clear_face();
    }
    else if(prev_butt == 2)
    {
        msg << QString().setNum(VALUE_REQUEST);
        msg << ui->re_edit->text() << ui->im_edit->text();
        clear_face();
    }
    else if(prev_butt == 3)
    {

        if(num <= size - 1)
        {

            msg << QString().setNum(CHANGE_POL_ROOTS_REQUEST);
            msg << ui->re_edit->text() << ui->im_edit->text();
            msg << QString().setNum(num + 1);

            //polin.change_roots(number(ui->re_edit->text().toDouble(), ui->im_edit->text().toDouble()), num);
            num++;
            ui->polin_num_label->setText(QString::number(num + 1));
            if(num - (size - 1) == 1)
            {
                ui->an_label_2->show();
                ui->polin_num_label->hide();
                ui->polin_text_label->hide();
            }

            ui->re_edit->clear();
            ui->im_edit->clear();

        }
        else if(num - (size - 1) == 1)
        {
            //ui->re_edit->clear();
            //ui->im_edit->clear();


            //ui->an_label_2->show();
            //ui->polin_num_label->hide();
            //ui->polin_text_label->hide();



            //double new_re = ui->re_edit->text().toDouble();
            //double new_im = ui->im_edit->text().toDouble();
            ui->re_edit->clear();
            ui->im_edit->clear();


            //number new_an = number(new_re, new_im);
            msg << QString().setNum(CHANGE_POL_AN_REQUEST);
            msg << ui->re_edit->text() << ui->im_edit->text();
            clear_face();
            num = 0;
            QString one = "1";
            ui->polin_num_label->setText(one);
            return;
        }

    }
    else if(prev_butt == 4)
    {
        if(ui->eprint_box->currentText() == "Классический")
        {
            msg << QString().setNum(PRINT_CLASSIC_REQUEST);
            clear_face();
        }
        else
        {
            msg << QString().setNum(PRINT_CANONIC_REQUEST);
            clear_face();
        }
    }
    else if(prev_butt == 5)
    {
        msg << QString().setNum(CHANGE_SIZE_REQUEST);
        msg << ui->new_size_edit->text();
        size = ui->new_size_edit->text().toInt();

        clear_face();
    }
    else if(prev_butt == 6)
    {
        msg << QString().setNum(CHANGE_ROOT_REQUEST);
        msg << ui->re_edit->text() << ui->im_edit->text();
        msg << ui->index_change_edit->text();

        clear_face();
    }

    emit request(msg);
}




void Interface::on_exit_buttom_clicked()
{
    close();
}

void Interface::answer(QString msg)
{
    QString text;
    int p = msg.indexOf(separator);
    int t = msg.left(p).toInt();
    msg = msg.mid(p+1,msg.length()-p-2);
    switch (t)
    {
    case VALUE_ANSWER:
        text = "p";
        p = msg.indexOf(separator);
        text += msg.left(p);
        text += " = ";
        text += msg.right(msg.length()-p-1);
        ui->result_line->setText(text);
        ui->x_label->hide();
        ui->re_edit->hide();
        ui->i_label->hide();
        ui->im_edit->hide();
        //submit_value_btn->hide();
        break;
    case PRINT_ANSWER:
        text = "p(x) = ";
        text += msg;
        ui->result_line->setText(text);
        ui->eprint_box->hide();
        //submit_print_btn->hide();
        break;
    case CHANGE_POL_ANSWER:
        ui->re_edit->setText("");
        ui->im_edit->setText("");
        break;
    case CHANGE_LAST_ANSWER:
        ui->size_label->hide();
        ui->new_size_edit->hide();
        ui->new_size_edit->setText("");
        //submit_change_size_btn->hide();
        ui->an_label->hide();
        ui->re_edit->hide();
        ui->re_edit->setText("");
        ui->i_label->hide();
        ui->im_edit->hide();
        ui->im_edit->setText("");
        ui->index_change_label->hide();
        ui->index_change_edit->hide();
        ui->index_change_edit->setText("");
        //submit_change_root_btn->hide();
        ui->an_label_2->hide();
        ui->re_edit->hide();
        ui->re_edit->setText("");
        ui->i_label->hide();
        ui->im_edit->hide();
        ui->im_edit->setText("");
        //submit_an_btn->hide();
        //submit_write_btn->hide();
        //write_mode->hide();
        //write_mode->setText("Введите an");
        ui->result_line->setText("Полином изменен");
        break;
    case SIZE_ANSWER:
        //size = msg.toInt();
    default: break;
    }
}
