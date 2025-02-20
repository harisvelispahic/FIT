using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TinyGameStore_G1.Extensions
{
    public static class Utils
    {
        public static byte[] ToByteArray(this Image image)
        {
            MemoryStream ms = new MemoryStream();
            image.Save(ms, System.Drawing.Imaging.ImageFormat.Png);
            return ms.ToArray();
        }

        public static Image ToImage(this byte[] bytes)
        {
            MemoryStream ms = new MemoryStream(bytes);
            return Image.FromStream(ms);
        }
    }
}
