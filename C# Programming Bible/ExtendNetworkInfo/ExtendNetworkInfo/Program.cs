using System;
using System.Net;
using System.Net.NetworkInformation;

class ExtendNetworkInfo
{
    static void Main(string[] args)
    {
        DisplayNetworkInfo();
    }

    public static void DisplayNetworkInfo()
    {
        NetworkInterface[] adapters =
            NetworkInterface.GetAllNetworkInterfaces();

        foreach (NetworkInterface adapter in adapters)
        {
            IPInterfaceProperties adapterProperties = adapter.GetIPProperties();
            GatewayIPAddressInformationCollection Gatewayaddresses =
                adapterProperties.GatewayAddresses;
            IPAddressCollection dhcpServers =
                adapterProperties.DhcpServerAddresses;
            IPAddressCollection dnsServers = adapterProperties.DnsAddresses;

            Console.WriteLine("네트워크 카드 : " + adapter.Description);
            Console.WriteLine(" Physical Address ............ : " +
                                    adapter.GetPhysicalAddress());
            Console.WriteLine(" IP Address .................. : " +
                                    Get_MyIP());

            if (Gatewayaddresses.Count > 0)
            {
                foreach (GatewayIPAddressInformation address in Gatewayaddresses)
                {
                    Console.WriteLine(" Gateway Address ........... : " +
                                            address.Address.ToString());
                }
            }

            if (dhcpServers.Count > 0)
            {
                foreach (IPAddress dhcp in dhcpServers)
                {
                    Console.WriteLine(" DHCP Servers ............ : " +
                                            dhcp.ToString());
                }
            }

            if (dnsServers.Count > 0)
            {
                foreach (IPAddress dns in dnsServers)
                {
                    Console.WriteLine(" DNS Servers ............. : " +
                                            dns.ToString());
                }
            }
        }

        while (true) { }
    }

    public static string Get_MyIP()
    {
        IPHostEntry host = Dns.GetHostEntry(Dns.GetHostName());
        string myip = host.AddressList[0].ToString();

        return myip;
    }
}
