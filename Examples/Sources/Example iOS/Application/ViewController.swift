//
//  ViewController.swift
//  Example iOS
//
//  Created by Panghu on 3/22/20.
//

import UIKit
import WALibrary

class ViewController: UITableViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        title = "WALibrary"
        tableView.register(UITableViewCell.self, forCellReuseIdentifier: "cell")
    }
    
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return 10
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        return tableView.dequeueReusableCell(withIdentifier: "cell", for: indexPath)
    }
    
    override func tableView(_ tableView: UITableView, willDisplay cell: UITableViewCell, forRowAt indexPath: IndexPath) {
        cell.textLabel?.text = "\(indexPath.item)"
    }
}
