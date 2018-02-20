namespace Server
{
    public partial class UIMainWindow : Form
    {
        private void addDeviceInfos(TreeNode device, Device dev)
        {
            original(device,dev);
            device.Nodes.Add("Betriebssystem: " + dev.OS);
            device.Nodes.Add("Prozessor: " + dev.CPU);
            device.Nodes.Add("Systemfestplatte: " + dev.HDD);
        }
    }
}
