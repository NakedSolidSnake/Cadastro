function Tabela ({array, select}) {
    return (
       <table className="table">
            <thead>
                <tr>
                    <th>#</th>
                    <th>Name</th>
                    <th>Address</th>
                    <th>Age</th>
                    <th>Action</th>
                </tr>
            </thead>
            <tbody>
                {
                    array.map ((object, index) => (
                        <tr key={index}>
                            <td>{object.id}</td>
                            <td>{object.name}</td>
                            <td>{object.address}</td>
                            <td>{object.age}</td>
                            <td><button onClick={() => {select (index)}} className="btn btn-success">Select</button></td>
                        </tr>
                    ))
                }
            </tbody>
       </table>
    )
}

export default Tabela;