#include "interface.h"
#include "ui_interface.h"
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

    number a_n(3, 0);
    number n_roots[] = {number(3, 0), number(2, 0), number(1, 0)};
    polin.change_size(3);
    polin.change_an(a_n);
    polin.change_roots(n_roots[0], 0);
    polin.change_roots(n_roots[1], 1);
    polin.change_roots(n_roots[2], 2);
    polin.change_print_mode(PrintModeClassic);

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

    if(prev_butt == 1)
    {
        double new_re;
        double new_im;

        new_re = ui->re_edit->text().toDouble();
        new_im = ui->im_edit->text().toDouble();

        number new_a_n = number(new_re, new_im);

        polin.change_an(new_a_n);

        QString str;
        str << polin;
        ui->result_line->setText(str);

        num = 0;
        clear_face();
    }
    else if(prev_butt == 2)
    {
        double new_re;
        double new_im;

        new_re = ui->re_edit->text().toDouble();
        new_im = ui->im_edit->text().toDouble();

        number new_x = number(new_re, new_im);

        QString str;
        str << polin.count_val(new_x);
        ui->result_line->setText(str);
        num = 0;

        clear_face();
    }
    else if(prev_butt == 3)
    {

        //polin.change_roots(number(ui->re_edit->text().toDouble(), ui->im_edit->text().toDouble()), num);
        if(num <= polin.get_size() - 1)
        {
            polin.change_roots(number(ui->re_edit->text().toDouble(), ui->im_edit->text().toDouble()), num);
            num++;
            ui->polin_num_label->setText(QString::number(num + 1));
            if(num - (polin.get_size() - 1) == 1)
            {
                ui->an_label_2->show();
                ui->polin_num_label->hide();
                ui->polin_text_label->hide();
            }

            ui->re_edit->clear();
            ui->im_edit->clear();

        }
        else if(num - (polin.get_size() - 1) == 1)
        {
            //ui->re_edit->clear();
            //ui->im_edit->clear();


            //ui->an_label_2->show();
            //ui->polin_num_label->hide();
            //ui->polin_text_label->hide();



            double new_re = ui->re_edit->text().toDouble();
            double new_im = ui->im_edit->text().toDouble();
            ui->re_edit->clear();
            ui->im_edit->clear();


            number new_an = number(new_re, new_im);
            polin.change_an(new_an);
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
            polin.change_print_mode(PrintModeClassic);
            QString s;
            s << polin;
            ui->result_line->setText(s);
            num = 0;

            clear_face();
        }
        else
        {
            polin.change_print_mode(PrintModeCanonic);
            QString s;
            s << polin;
            ui->result_line->setText(s);
            num = 0;

            clear_face();
        }
    }
    else if(prev_butt == 5)
    {
        int new_N = ui->new_size_edit->text().toInt();
        polin.change_size(new_N);
        ui->result_line->setText("Размер изменен");
        num = 0;

        clear_face();
    }
    else if(prev_butt == 6)
    {
        int index = ui->index_change_edit->text().toInt();
        number root = number(ui->re_edit->text().toDouble(), ui->im_edit->text().toDouble());
        if((index > polin.get_size() - 1) || (index < 0))
        {
            ui->result_line->setText("Введен неверный индекс");
            num = 0;

            clear_face();
        }
        else
        {
            polin.change_roots(root, index);
            ui->result_line->setText("Корень изменен");
            num = 0;

            clear_face();
        }
    }
    else
    {
        ui->result_line->setText("Вы ничего не выбрали!");
    }
}




void Interface::on_exit_buttom_clicked()
{
    close();
}

