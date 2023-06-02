using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Singleton
{
    public partial class NewForm : Form
    {
        public NewForm()
        {
            InitializeComponent();
        }

        private static NewForm instance;
        public static NewForm GetInstance()
        {
            if (instance == null || instance.IsDisposed)
                instance = new NewForm();
            else
            {
                instance.BringToFront();
            }

            return instance;
        }
    }
}
