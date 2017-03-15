extern crate byteorder;
extern crate clap;
extern crate hidapi;

extern crate mjolnir;


use clap::{App, Arg, ArgMatches, SubCommand};


fn main() {
    let args = parse_args();

    let api = hidapi::HidApi::get().expect("unable to initialize hidapi");

    if args.subcommand_matches("devices").is_some() {
        println!("Vendor Id: {:04x}\n", mjolnir::flash::VENDOR_ID);

        for d in api.devices() {
            print_device_info(&d);
        }
    }

    if let Some(matches) = args.subcommand_matches("flash") {
        let firmware = &matches.value_of("firmware").expect("unable to open firmware");

        let devices = mjolnir::flash::search_devices(&api);

        if devices.is_empty() {
            println!("No devices found!");
            return;
        }

        println!("Found {} devices\n", devices.len());
        print_device_info(&devices[0]);

        if let Err(ref what) = mjolnir::flash::flash(&api, &devices[0], firmware) {
            println!("{}", what);
        }
    }

}

fn parse_args<'a>() -> ArgMatches<'a> {
    App::new("Flesciathor")
        .version("0.1")
        .author("Daniele D'Orazio")
        .about("Hammer down your keyboard until it works")
        .subcommand(SubCommand::with_name("devices").about("List all the devices"))
        .subcommand(SubCommand::with_name("flash")
            .about("Flash")
            .arg(Arg::with_name("firmware").required(true)))
        .get_matches()
}


fn print_device_info(d: &hidapi::HidDeviceInfo) {
    println!("Path: {}", d.path);
    println!("VendorId: {:04x}", d.vendor_id);
    println!("ProductId: {:04x}", d.product_id);

    if let Some(ref serial) = d.serial_number {
        println!("Serial Number: {}", serial);
    }

    println!("Release: {}", d.release_number);

    if let Some(ref manufacturer) = d.manufacturer_string {
        println!("Manufacturer String: {}", manufacturer);
    }

    if let Some(ref product) = d.product_string {
        println!("Manufacturer String: {}", product);
    }

    println!("");
}
