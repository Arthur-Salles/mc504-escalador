//
//  MachinesView.swift
//  SeisEncaixesViewer
//
//  Created by Ariadne Bigheti on 21/05/23.
//

import SwiftUI

struct MachinesView: View {
    @Binding var machines: [MachineViewModel]
    private let adaptativeColumns = [
        GridItem(.adaptive(minimum: 250), alignment: .leading)
    ]
    
    var body: some View {

        LazyVGrid(columns: adaptativeColumns, spacing: 20)  {
            ForEach($machines) { machine in
                    MachineView(viewModel: machine)
                
            }
            
        }
        .padding(50)
        
    }
}


