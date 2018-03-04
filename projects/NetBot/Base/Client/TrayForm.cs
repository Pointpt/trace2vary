using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Client
{
    public partial class TrayForm : Form
    {
        Controller controller;
        public TrayForm()
        {
            InitializeComponent();
        }


        private void TrayForm_Load(object sender, EventArgs e)
        {
            controller = new Controller(this);
            this.WindowState = FormWindowState.Minimized;
            Tray.ContextMenu.MenuItems.Find("autoAnmeldung", false)[0].Checked = Configuration.AutomatischeAnmeldung;
        }

        private void TrayForm_Resize(object sender, EventArgs e)
        {
            if (this.WindowState == FormWindowState.Minimized)
            {


                this.TrayIcon.ContextMenu = controller.createClientMenu();
                this.ShowInTaskbar = false;
                this.WindowState = FormWindowState.Minimized;
                this.TrayIcon.Visible = true;
            }
        }

        public void Update()
        {
            if (Configuration.AutomatischeAnmeldung)
            {
                Tray.ContextMenu.MenuItems.Find("autoAnmeldung", false)[0].Checked = true;
            }
            else
            {
                Tray.ContextMenu.MenuItems.Find("autoAnmeldung", false)[0].Checked = false;
            }
        }
        
        public NotifyIcon Tray
        {
            get { return this.TrayIcon; }
        }
    }
}
