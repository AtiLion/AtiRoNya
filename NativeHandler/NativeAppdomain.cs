using System;
using System.IO;
using System.Reflection;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NativeHandler
{
    internal sealed class NativeAppDomain : AppDomainManager, INetDomain
    {
        public NativeAppDomain() { }

        #region AppDomainManager Functions
        public override void InitializeNewDomain(AppDomainSetup appDomainInfo)
        {
            InitializationFlags = AppDomainManagerInitializationOptions.RegisterWithHost;
        }
        #endregion

        #region Custom Functions
        public void LoadAssembly(string assembly)
        {
            if (!File.Exists(assembly))
                return;

            Assembly.Load(File.ReadAllBytes(assembly));
        }
        public void LoadAssemblyAndExecute(string assembly)
        {
            if (!File.Exists(assembly))
                return;
            Assembly netAssembly = Assembly.Load(File.ReadAllBytes(assembly));

            if (netAssembly == null) // Assembly not found
                return;
            Type t = netAssembly.GetType("Bootloader");

            if (t == null) // Bootloader not found
                return;
            MethodInfo method = t.GetMethod("Main", BindingFlags.Static | BindingFlags.Public | BindingFlags.NonPublic);

            if (method == null) // Method not found
                return;

            try
            {
                method.Invoke(null, new object[0]);
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex);
            }
        }
        public void LoadMods(string path)
        {
            if (!Directory.Exists(path))
                return;
            List<Assembly> assemblies = new List<Assembly>();

            // Load the assemblies
            foreach (string assembly in Directory.EnumerateFiles(path, "*.dll", SearchOption.TopDirectoryOnly))
            {
                try
                {
                    assemblies.Add(Assembly.Load(File.ReadAllBytes(assembly)));
                }
                catch(Exception ex)
                {
                    Console.WriteLine(ex);
                }
            }

            // Execute the mods
            foreach(Assembly assembly in assemblies)
            {
                Type t = assembly.GetType("Bootloader");

                if(t == null) // Probably a library
                    continue;
                MethodInfo method = t.GetMethod("Main", BindingFlags.Static | BindingFlags.Public | BindingFlags.NonPublic);

                if (method == null) // A library with a similar name
                    continue;
                
                // Try and invoke
                try
                {
                    method.Invoke(null, new object[0]);
                } 
                catch(Exception ex) { }
            }
            return;
        }
        #endregion
    }
}
