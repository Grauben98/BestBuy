﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BestBuy_Proyecto
{   
    public partial class frmSearch : Form
    {
        public static Form form;
        public frmSearch()
        {
            InitializeComponent();
            form=this;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            frmSelectProduct SelectProduct = new frmSelectProduct(form);
            SelectProduct.Show();
            this.Hide();
        }
    }
}
