using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Primitives;
using Newtonsoft.Json;
using NxtDownloader.Models;

namespace NxtDownloader.Controllers
{
    public class HomeController : Controller
    {
        private static readonly HttpClient Client = new HttpClient();
        public async Task<IActionResult> Index()
        {
            Client.DefaultRequestHeaders.Accept.Clear();
            Client.DefaultRequestHeaders.Accept.Add(
                new MediaTypeWithQualityHeaderValue("application/vnd.github.v3+json"));
            Client.DefaultRequestHeaders.Add("User-Agent", ".NET Foundation Repository Reporter");

            var stringTask = Client.GetStringAsync("https://api.github.com/repos/aau-hcl-p5/main/branches");

            return View(JsonConvert.DeserializeObject<List<Branch>>(await stringTask));
        }
        
        public IActionResult Download(string downloadString)
        {
            var res = new StringBuilder();
            var data = Convert.FromBase64String(downloadString);
            var decodedString = Encoding.UTF8.GetString(data);
            
            res.AppendLine($"{downloadString} --> {decodedString}");
            
            var isUrl = decodedString.Contains(".");

            res.AppendLine(decodedString + " is determined to be a " + (isUrl ? "URL" : "branch"));

            var downloadUrl = isUrl
                ? decodedString
                : "http://hcl.codes/teamcity/guestAuth/repository/download/P5_Build/.lastSuccessful/nxt_OSEK.rxe?branch=" +
                  Uri.EscapeDataString(decodedString);
            
            res.AppendLine("Downloading from url: " + downloadUrl + "...");
            
            using (var client = new WebClient())
            {
                try
                {
                    client.DownloadFile(downloadUrl, "nxt_OSEK.rxe");
                    Process cmd = new Process
                    {
                        StartInfo =
                        {
                            FileName = "/bin/bash",
                            RedirectStandardInput = true,
                            RedirectStandardOutput = true,
                            CreateNoWindow = true,
                            UseShellExecute = false
                        }
                    };
                    cmd.Start();
                    cmd.StandardInput.WriteLine("cat nxt_OSEK.rxe");
                    cmd.StandardInput.Flush();
                    cmd.StandardInput.Close();
                    cmd.WaitForExit();
                    res.AppendLine(cmd.StandardOutput.ReadToEnd());
                    res.AppendLine("Success!");
                }
                catch (Exception e)
                {
                    res.AppendLine("Exception:" + e);
                    res.AppendLine(e.StackTrace);
                }
            }
            return Content(res.ToString());
        }


        public IActionResult Error()
        {
            return View(new ErrorViewModel {RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier});
        }
    }
}