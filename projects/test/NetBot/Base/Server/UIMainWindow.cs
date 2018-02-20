using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Server
{
    public partial class UIMainWindow : Form
    {
        //Controller zur Systemsteuerung
        Controller controller;

        //Statusmeldungen
        String statusText = "";

        public UIMainWindow()
        {
            InitializeComponent();
            controller = new Controller(this);
        }

        private void UIMainWindow_Load(object sender, EventArgs e)
        {
            controller.saveConfiguration();
            controller.createServer();
        }

        private void Update()
        {
            pcTreeView.Nodes.Clear();
            
            //Devices Liste
            TreeNode root = new TreeNode("Geräte");
            pcTreeView.Nodes.Add(root);
            foreach (Device dev in Data.Devices)
            {
                TreeNode device = new TreeNode(dev.Name);
                if (!dev.isLogin)
                    device.ForeColor = Color.Red;
                addDeviceInfos(device,dev);
                //Device an Liste anhängen
                root.Nodes.Add(device);
            }
            root.Expand();
        }

        private void addDeviceInfos(TreeNode device, Device dev)
        {
            device.Nodes.Add(new TreeNode("Verbindung", new TreeNode[] { new TreeNode("IP: " + dev.IP), new TreeNode("Port: " + dev.Port) }));
        }

        public void OnUpdateEvent()
        {
            EventHandler e = new EventHandler(this.UpdateEvent);
            this.Invoke(e);
        }

        public void UpdateEvent(object Sender, EventArgs e)
        {
            Update();
        }

        public void OnStatusEvent(String msg)
        {
            EventHandler e = new EventHandler(this.StatusEvent);
            statusText = msg;
            this.Invoke(e);
        }

        public void StatusEvent(object Sender, EventArgs e)
        {
            statusBarTextLabel.Text = statusText;
        }


        private void aktualisierenToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Update();
        }

        private void UIMainWindow_FormClosed(object sender, FormClosedEventArgs e)
        {
            controller.Dispose();
        }
    }
}
