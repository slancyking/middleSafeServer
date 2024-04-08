using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SixLabors.ImageSharp;
using SixLabors.ImageSharp.Formats;

namespace testImageLoad
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        static public void testLoadImage()
        { 
            WebRequest request = WebRequest.Create("http://client-profile-photo.eateapp.com/headIcon/7890053.jpg");
            WebResponse response = request.GetResponse();
            Stream reader = response.GetResponseStream();
            IImageFormat format;

            List<byte> bytes = new List<byte>();
            int temp = reader.ReadByte();
            while (temp != -1)
            {
                bytes.Add((byte)temp);
                temp = reader.ReadByte();
            }
            byte[] imgBytes = bytes.ToArray(); 

             
            SixLabors.ImageSharp.Image tmpImage = SixLabors.ImageSharp.Image.Load(imgBytes, out format);
            reader.Flush();
            reader.Close();
            reader.Dispose();
            response.Close();
            response.Dispose();


            uint Image64Size = (uint)(tmpImage.Width * tmpImage.Height);
            string image = Convert.ToBase64String(imgBytes);

            tmpImage.Dispose();

        }


        private void Form1_Load(object sender, EventArgs e)
        {
            testLoadImage();
        }
    }
}
